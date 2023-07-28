#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <typeinfo>
#include <math.h>

#include <xrt.h>
#include <experimental/xrt_kernel.h>

#define AIE_KERNEL_NUMBER 7
#define BUS_DWIDTH 256
#define DWIDTH 32
#define DATA_NUM (BUS_DWIDTH / DWIDTH)

typedef struct {
    int data[8];
} data_bus;

void cal_ref(int* input_buffer, unsigned width, unsigned height, int* kernel_coeff, int* ref_buffer);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File>" << std::endl;
        return EXIT_FAILURE;
    }

    /////////////////////////////////////////////////
    // Get device index and download xclbin
    /////////////////////////////////////////////////
    std::cout << "Open the device" << std::endl;
    auto device = xrt::device(0);
    std::string binaryFile = argv[1];
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    /////////////////////////////////////////////////
    // Get reference to the kernels
    /////////////////////////////////////////////////
    std::cout << "Get references to compute units" << std::endl;
    auto tile_mm2s_1    = xrt::kernel(device, uuid, "tile_mm2s:{tile_mm2s1}");
    auto sticker_s2mm_1 = xrt::kernel(device, uuid, "sticker_s2mm:{sticker_s2mm1}");

    /////////////////////////////////////////////////
    // Allocating Buffer in Global Memory
    /////////////////////////////////////////////////
    std::cout << "Allocate Buffer in Global Memory" << std::endl;
    unsigned img_width   = 720;
    unsigned img_height  = 480;
    unsigned img_number  = 2;
    unsigned tile_width  = 64;
    unsigned tile_height = 32;
    
    // 所有 img 中的元素个数
    unsigned img_element_number  = img_width * img_height * img_number;
    // 单个 tile 中的元素个数
    unsigned tile_element_number = tile_width * tile_height;

    // 每张图片的 tile 个数（width 和 height 两个维度）
    unsigned tile_width_number   = ceil((float)(img_width  - tile_width)  / (tile_width  - 2)) + 1;
	unsigned tile_height_number  = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

    // 每个 aie kernel 需要循环计算的总次数
    unsigned iteration = ceil((float)(tile_width_number * tile_height_number) / AIE_KERNEL_NUMBER) * img_number;
    
    // 所有输入图片的拼接后的大小
    size_t img_buffer_size  = BUS_DWIDTH * (img_element_number / DATA_NUM);

    // 用来存储所有的图片
    // host mem ------> device mem (img_in_buffer)
    // 后续：img_in_buffer ---(PL:tile_mm2s_1)---> aie kernel
    auto img_in_buffer = xrt::bo(device, img_buffer_size, tile_mm2s_1.group_id(0));
    
    // 用来存储最后的计算结果
    // aie kernel ---(PL:sticker_s2mm_1)---> img_out_buffer
    // 后续：device mem (img_out_buffer) ------> host mem
    auto img_out_buffer = xrt::bo(device, img_buffer_size, sticker_s2mm_1.group_id(7));

    /////////////////////////////////////////////////
    // Read data from file 
    /////////////////////////////////////////////////
    std::cout << "Read data from file" << std::endl;
    auto *img_input      = new int [img_element_number];
    auto *img_output_aie = new int [img_element_number];
    auto *img_placeholder= new int [img_element_number];
    auto *img_output_ref = new int [img_element_number];

    for (unsigned int i = 0; i < img_element_number; i++) {
        img_input[i] = rand() % 10;
    }

    // /////////////////////////////////////////////////
    // // Concatenate the input data
    // /////////////////////////////////////////////////
    // std::cout << "Concatenate the input data" << std::endl;
    // auto *img_input_con = new data_bus [img_element_number / DATA_NUM];
    // for (int i = 0; i < img_element_number / DATA_NUM; i++) {
    //     for (int j = 0; j < DATA_NUM; j++) {
    //         img_input_con[i].data[j] = img_input[i * DATA_NUM + j];
    //     }
    // }

    /////////////////////////////////////////////////
    // Cal output reference
    /////////////////////////////////////////////////
    std::cout << "Cal output reference" << std::endl;
    int kernel_coeff[16] = {64, 128, 64, 128, 256, 128, 64, 128, 64};
    for (unsigned img_index = 0; img_index < img_number; img_index++) {
    	cal_ref(img_input + img_index * img_width * img_height, img_width, img_height, kernel_coeff, img_output_ref + img_index * img_width * img_height);
    }

    auto start = chrono::steady_clock::now();
    
    /////////////////////////////////////////////////
    // Write input data to device global memory
    /////////////////////////////////////////////////
    std::cout << "Write input data to device global memory" << std::endl;
    img_in_buffer.write(img_input);

    /////////////////////////////////////////////////
    // Synchronize input buffers data to device global memory
    /////////////////////////////////////////////////
    std::cout << "Synchronize input buffers data to device global memory" << std::endl;
    img_in_buffer.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto end = chrono::steady_clock::now();

    std::cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << std::endl;

    /////////////////////////////////////////////////
    // Execute the PL compute units
    /////////////////////////////////////////////////
    std::cout << "Run the PL kernels" << std::endl;

    std::cout << "Run the sticker PL" << std::endl;
    auto run_sticker_s2mm_1 = sticker_s2mm_1(
	    nullptr, nullptr, nullptr, nullptr, nullptr,
	    nullptr, nullptr, 
	    img_out_buffer);

    std::cout << "Run the tile PL" << std::endl;
    auto run_tile_mm2s_1 = tile_mm2s_1(
	    img_in_buffer, 
	    nullptr, nullptr, nullptr, nullptr, nullptr,
	    nullptr, nullptr);

    run_tile_mm2s_1.wait();
    std::cout << "tile_mm2s_1 completed" << std::endl;

    run_sticker_s2mm_1.wait();
    std::cout << "sticker_s2mm_1 completed" << std::endl;

    /////////////////////////////////////////////////
    // Synchronize the output buffer data from the device
    ///////////////////////////////////////////////
    std::cout << "Synchronize output buffers data to device global memory" << std::endl;
    img_out_buffer.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

    // /////////////////////////////////////////////////
    // // Read output buffer data to local buffer
    // /////////////////////////////////////////////////
    std::cout << "Read output data from device global memory" << std::endl;
    auto *img_output_aie_con = new data_bus [img_element_number / DATA_NUM];
    img_out_buffer.read(img_output_aie);

    /////////////////////////////////////////////////
    // Split the output data
    /////////////////////////////////////////////////
    // std::cout << "Split the output data" << std::endl;
    // for (int i = 0; i < img_element_number / DATA_NUM; i++) {
    //     for (int j = 0; j < DATA_NUM; j++) {
    //         img_output_aie[i * DATA_NUM + j] = img_output_aie_con[i].data[j];
    //     }
    // }

    /////////////////////////////////////////////////
    // Correctness verification
    /////////////////////////////////////////////////
    std::cout << "Correctness verification" << std::endl;
    unsigned erro = 0;
    for (unsigned i = 0; i < img_element_number; i++) {
        if (abs(img_output_aie[i] - img_output_ref[i]) > 1e-3) {
            erro++;
        }
    }
    std::cout << "Erro time: " << erro << std::endl;

    /////////////////////////////////////////////////
    // Writing data to output file
    /////////////////////////////////////////////////
    std::cout << "Writing data to output file" << std::endl;
    std::ofstream outputfile;
    std::cout << "Ref Out1 " << std::to_string(img_output_ref[0]) << std::endl;
    std::cout << "AIE Out1 " << std::to_string(img_output_aie[0]) << std::endl;
    outputfile.open("build.hw/aie_hw_run_data/output.txt");
    for (unsigned i = 0; i < img_element_number; i++) {
        outputfile << img_output_aie[i] << std::endl;
    }
    outputfile.close();

    delete [] img_input;
    delete [] img_output_aie;
    delete [] img_output_ref;
    delete [] img_input_con;
    delete [] img_output_aie_con;

    return 0;
}

void cal_ref(int* input_buffer, unsigned width, unsigned height, int* kernel_coeff, int* ref_buffer) {
    unsigned padding_width   = width + 2;
    unsigned padding_height  = height + 2;
    unsigned padding_elements_number = padding_width * padding_height;
    auto     *padding_buffer = new int [padding_elements_number];

    // 对输入图片进行 padding
    // 首先将 input_buffer 全部拷贝到 padding_buffer “中间“ 区域
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            padding_buffer[(i + 1) * padding_width + (j + 1)] = input_buffer[i * width + j];
        }
    }

    // 对 padding_buffer 四个角的元素赋值 
    padding_buffer[0]                                    = padding_buffer[padding_width + 1];
    padding_buffer[padding_width - 1]                    = padding_buffer[2 * padding_width - 2];
    padding_buffer[(padding_height - 1) * padding_width] = padding_buffer[(padding_height - 2) * padding_width + 1];
    padding_buffer[padding_height * padding_width - 1]   = padding_buffer[(padding_height - 1) * padding_width - 2];

    // 对 padding_buffer 剩下的四条边进行赋值
    for (unsigned i = 1; i < padding_width - 1; i++) {
        padding_buffer[i] = padding_buffer[i + padding_width];
    }
    for (unsigned i = 1; i < padding_height - 1; i++) {
        padding_buffer[i * padding_width]           = padding_buffer[i * padding_width + 1];
        padding_buffer[(i + 1) * padding_width - 1] = padding_buffer[(i + 1) * padding_width - 2];
    }
    for (unsigned i = 1; i < padding_width - 1; i++) {
        padding_buffer[(padding_height - 1) * padding_width + i] = padding_buffer[(padding_height - 2) * padding_width + i];
    }

    // 对 padding 后的图片进行卷积运算
    unsigned width_loop  = padding_width - 2;
    unsigned height_loop = padding_height - 2;
    for (unsigned i = 0; i < height_loop; i++) {
        for (unsigned j = 0; j < width_loop; j++) {
            ref_buffer[i * width + j] = 0;
            for (unsigned x = 0; x < 3; x++) {
                for (unsigned y = 0; y < 3; y++) {
                    ref_buffer[i * width + j] += kernel_coeff[x * 3 + y] * padding_buffer[(i + x) * padding_width + j + y];
                }
            }
        }
    }

	delete [] padding_buffer;
}
