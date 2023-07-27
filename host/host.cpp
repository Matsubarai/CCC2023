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

#include <xrt.h>
#include <experimental/xrt_kernel.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File>" << std::endl;
        return EXIT_FAILURE;
    }

    // Get device index and download xclbin
    std::cout << "Open the device" << std::endl;
    auto device = xrt::device(0);
    std::string binaryFile = argv[1];
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    // Get reference to the kernels
    std::cout << "Get references to compute units" << std::endl;
    auto tile_mm2mm_1 = xrt::kernel(device, uuid, "tile_mm2mm:{tile_mm2mm1}");
    auto sitcker_mm2mm_1 = xrt::kernel(device, uuid, "sticker_mm2mm:{sticker_mm2mm1}");
    unsigned aie_kernel_number = 15;
    std::array<xrt::kernel, aie_kernel_number> mm2s_;
    std::array<xrt::kernel, aie_kernel_number> s2mm_;
    for (unsigned i = 0; i < mm2s_.size(); ++i) {
        std::string cu_name = "mm2s:{mm2s" + std::to_string(i+1) + "}";
        mm2s_[i] = xrt::kernel(device, uuid, cu_name.c_str());
    }
    for (unsigned i = 0; i < s2mm_.size(); ++i) {
        std::string cu_name = "s2mm:{s2mm" + std::to_string(i+1) + "}";
        s2mm_[i] = xrt::kernel(device, uuid, cu_name.c_str());
    }
    // auto mm2s_1 = xrt::kernel(device, uuid, "mm2s:{mm2s1}");
    // auto mm2s_2 = xrt::kernel(device, uuid, "mm2s:{mm2s2}");
    // auto mm2s_3 = xrt::kernel(device, uuid, "mm2s:{mm2s3}");
    // auto mm2s_4 = xrt::kernel(device, uuid, "mm2s:{mm2s4}");
    // auto mm2s_5 = xrt::kernel(device, uuid, "mm2s:{mm2s5}");
    // auto mm2s_6 = xrt::kernel(device, uuid, "mm2s:{mm2s6}");
    // auto mm2s_7 = xrt::kernel(device, uuid, "mm2s:{mm2s7}");
    // auto mm2s_8 = xrt::kernel(device, uuid, "mm2s:{mm2s8}");
    // auto mm2s_9 = xrt::kernel(device, uuid, "mm2s:{mm2s9}");
    // auto mm2s_10 = xrt::kernel(device, uuid, "mm2s:{mm2s10}");
    // auto mm2s_11 = xrt::kernel(device, uuid, "mm2s:{mm2s11}");
    // auto mm2s_12 = xrt::kernel(device, uuid, "mm2s:{mm2s12}");
    // auto mm2s_13 = xrt::kernel(device, uuid, "mm2s:{mm2s13}");
    // auto mm2s_14 = xrt::kernel(device, uuid, "mm2s:{mm2s14}");
    // auto mm2s_15 = xrt::kernel(device, uuid, "mm2s:{mm2s15}");

    // auto s2mm_1 = xrt::kernel(device, uuid, "s2mm:{s2mm1}");
    // auto s2mm_2 = xrt::kernel(device, uuid, "s2mm:{s2mm2}");
    // auto s2mm_3 = xrt::kernel(device, uuid, "s2mm:{s2mm3}");
    // auto s2mm_4 = xrt::kernel(device, uuid, "s2mm:{s2mm4}");
    // auto s2mm_5 = xrt::kernel(device, uuid, "s2mm:{s2mm5}");
    // auto s2mm_6 = xrt::kernel(device, uuid, "s2mm:{s2mm6}");
    // auto s2mm_7 = xrt::kernel(device, uuid, "s2mm:{s2mm7}");
    // auto s2mm_8 = xrt::kernel(device, uuid, "s2mm:{s2mm8}");
    // auto s2mm_9 = xrt::kernel(device, uuid, "s2mm:{s2mm9}");
    // auto s2mm_10 = xrt::kernel(device, uuid, "s2mm:{s2mm10}");
    // auto s2mm_11 = xrt::kernel(device, uuid, "s2mm:{s2mm11}");
    // auto s2mm_12 = xrt::kernel(device, uuid, "s2mm:{s2mm12}");
    // auto s2mm_13 = xrt::kernel(device, uuid, "s2mm:{s2mm13}");
    // auto s2mm_14 = xrt::kernel(device, uuid, "s2mm:{s2mm14}");
    // auto s2mm_15 = xrt::kernel(device, uuid, "s2mm:{s2mm15}");

    // Allocating the input size of sizeIn to MM2S
    std::cout << "Allocate Buffer in Global Memory" << std::endl;
    unsigned img_width     = 720;
    unsigned img_height = 480;
    unsigned img_number = 2;
    unsigned img_num_elements = img_width * img_height * img_number;

    unsigned tile_width = 64;
    unsigned tile_height       = 32;

    unsigned tile_num_width = ceil((float)(img_width - tile_width) / (tile_width - 2)) + 1;
	unsigned tile_num_height = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

    unsigned iteration = ceil((float)(tile_num_width * tile_num_height) / aie_kernel_number) * img_number;
    
    unsigned tile_num_elements = tile_width * tile_height;
    size_t img_size_in_bytes = sizeof(int) * img_num_elements;
    size_t tile_size_in_bytes = sizeof(int) * tile_num_elements * iteration;
    auto img_in_buff = xrt::bo(device, img_size_in_bytes, tile_mm2mm_1.group_id(0));
    auto in_buff_1 = xrt::bo(device, tile_size_in_bytes, mm2s_1.group_id(0));
    auto in_buff_2 = xrt::bo(device, tile_size_in_bytes, mm2s_2.group_id(0));
    auto in_buff_3 = xrt::bo(device, tile_size_in_bytes, mm2s_3.group_id(0));
    auto in_buff_4 = xrt::bo(device, tile_size_in_bytes, mm2s_4.group_id(0));
    auto in_buff_5 = xrt::bo(device, tile_size_in_bytes, mm2s_5.group_id(0));
    auto in_buff_6 = xrt::bo(device, tile_size_in_bytes, mm2s_6.group_id(0));
    auto in_buff_7 = xrt::bo(device, tile_size_in_bytes, mm2s_7.group_id(0));
    auto in_buff_8 = xrt::bo(device, tile_size_in_bytes, mm2s_8.group_id(0));
    auto in_buff_9 = xrt::bo(device, tile_size_in_bytes, mm2s_9.group_id(0));
    auto in_buff_10 = xrt::bo(device, tile_size_in_bytes, mm2s_10.group_id(0));
    auto in_buff_11 = xrt::bo(device, tile_size_in_bytes, mm2s_11.group_id(0));
    auto in_buff_12 = xrt::bo(device, tile_size_in_bytes, mm2s_12.group_id(0));
    auto in_buff_13 = xrt::bo(device, tile_size_in_bytes, mm2s_13.group_id(0));
    auto in_buff_14 = xrt::bo(device, tile_size_in_bytes, mm2s_14.group_id(0));
    auto in_buff_15 = xrt::bo(device, tile_size_in_bytes, mm2s_15.group_id(0));

    auto img_out_buff = xrt::bo(device, img_size_in_bytes, sticker_mm2mm_1.group_id(0));
    auto out_buff_1 = xrt::bo(device, tile_size_in_bytes, s2mm_1.group_id(0));
    auto out_buff_2 = xrt::bo(device, tile_size_in_bytes, s2mm_2.group_id(0));
    auto out_buff_3 = xrt::bo(device, tile_size_in_bytes, s2mm_3.group_id(0));
    auto out_buff_4 = xrt::bo(device, tile_size_in_bytes, s2mm_4.group_id(0));
    auto out_buff_5 = xrt::bo(device, tile_size_in_bytes, s2mm_5.group_id(0));
    auto out_buff_6 = xrt::bo(device, tile_size_in_bytes, s2mm_6.group_id(0));
    auto out_buff_7 = xrt::bo(device, tile_size_in_bytes, s2mm_7.group_id(0));
    auto out_buff_8 = xrt::bo(device, tile_size_in_bytes, s2mm_8.group_id(0));
    auto out_buff_9 = xrt::bo(device, tile_size_in_bytes, s2mm_9.group_id(0));
    auto out_buff_10 = xrt::bo(device, tile_size_in_bytes, s2mm_10.group_id(0));
    auto out_buff_11 = xrt::bo(device, tile_size_in_bytes, s2mm_11.group_id(0));
    auto out_buff_12 = xrt::bo(device, tile_size_in_bytes, s2mm_12.group_id(0));
    auto out_buff_13 = xrt::bo(device, tile_size_in_bytes, s2mm_13.group_id(0));
    auto out_buff_14 = xrt::bo(device, tile_size_in_bytes, s2mm_14.group_id(0));
    auto out_buff_15 = xrt::bo(device, tile_size_in_bytes, s2mm_15.group_id(0));

    // Read data from file 
    auto *DataInput = new int [img_num_elements];

    auto *DataOutput = new int [img_num_elements];

    for (unsigned int i = 0; i < img_num_elements; i++) {
        DataInput[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
    }

    img_in_buff.write(DataInput);

    // Synchronize input buffers data to device global memory
    std::cout << "Synchronize input buffers data to device global memory" << std::endl;
    img_in_buff.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    // Execute the compute units
    std::cout << "Run the kernels" << std::endl;

    

    auto run_tile_mm2mm_1 = tile_mm2mm_1<img_width, img_height, tile_width, data_width>(img_in_buff, -----, 0, 0);
    run_tile_mm2mm_1.wait();

    for (unsigned i = 0; i < img_number; i++) {

        for (unsigned j = 0; j < aie_kernel_number; j++) {

            for (unsigned k = 0; k < iteration; k++) {

                

            }

        }

        // for (unsigned ti = 0; ti < tile_num_height; ti++) {
        //     for (unsigned tj = 0; tj < tile_num_width; tj++) {
        //         if (i == 0 && ti == 0 && tj ==0)
        //             continue;
        //         unsigned aie_index = (ti * tile_num_width + tj) % aie_kernel_number;
                
        //         run_tile_mm2mm_1.set_arg(1, -----);
        //         run_tile_mm2mm_1.set_arg(2, tj);
        //         run_tile_mm2mm_1.set_arg(3, ti);
        //         run_tile_mm2mm_1.start();
        //         run_tile_mm2mm_1.wait();

        //     }
        // }

    }

    auto run_s2mm_1 = s2mm_1(out_buff_1, nullptr, tile_size_in_bytes);
    auto run_s2mm_2 = s2mm_2(out_buff_2, nullptr, tile_size_in_bytes);
    auto run_s2mm_3 = s2mm_3(out_buff_3, nullptr, tile_size_in_bytes);
    auto run_s2mm_4 = s2mm_4(out_buff_4, nullptr, tile_size_in_bytes);
    auto run_s2mm_5 = s2mm_5(out_buff_5, nullptr, tile_size_in_bytes);
    auto run_s2mm_6 = s2mm_6(out_buff_6, nullptr, tile_size_in_bytes);
    auto run_s2mm_7 = s2mm_7(out_buff_7, nullptr, tile_size_in_bytes);
    auto run_s2mm_8 = s2mm_8(out_buff_8, nullptr, tile_size_in_bytes);
    auto run_s2mm_9 = s2mm_9(out_buff_9, nullptr, tile_size_in_bytes);
    auto run_s2mm_10 = s2mm_10(out_buff_10, nullptr, tile_size_in_bytes);
    auto run_s2mm_11 = s2mm_11(out_buff_11, nullptr, tile_size_in_bytes);
    auto run_s2mm_12 = s2mm_12(out_buff_12, nullptr, tile_size_in_bytes);
    auto run_s2mm_13 = s2mm_13(out_buff_13, nullptr, tile_size_in_bytes);
    auto run_s2mm_14 = s2mm_14(out_buff_14, nullptr, tile_size_in_bytes);
    auto run_s2mm_15 = s2mm_15(out_buff_15, nullptr, tile_size_in_bytes);
 
    auto run_mm2s_1 = mm2s_1(in_buff_1, nullptr, tile_size_in_bytes);
    auto run_mm2s_2 = mm2s_2(in_buff_2, nullptr, tile_size_in_bytes);
    auto run_mm2s_3 = mm2s_3(in_buff_3, nullptr, tile_size_in_bytes);
    auto run_mm2s_4 = mm2s_4(in_buff_4, nullptr, tile_size_in_bytes);
    auto run_mm2s_5 = mm2s_5(in_buff_5, nullptr, tile_size_in_bytes);
    auto run_mm2s_6 = mm2s_6(in_buff_6, nullptr, tile_size_in_bytes);
    auto run_mm2s_7 = mm2s_7(in_buff_7, nullptr, tile_size_in_bytes);
    auto run_mm2s_8 = mm2s_8(in_buff_8, nullptr, tile_size_in_bytes);
    auto run_mm2s_9 = mm2s_9(in_buff_9, nullptr, tile_size_in_bytes);
    auto run_mm2s_10 = mm2s_10(in_buff_10, nullptr, tile_size_in_bytes);
    auto run_mm2s_11 = mm2s_11(in_buff_11, nullptr, tile_size_in_bytes);
    auto run_mm2s_12 = mm2s_12(in_buff_12, nullptr, tile_size_in_bytes);
    auto run_mm2s_13 = mm2s_13(in_buff_13, nullptr, tile_size_in_bytes);
    auto run_mm2s_14 = mm2s_14(in_buff_14, nullptr, tile_size_in_bytes);
    auto run_mm2s_15 = mm2s_15(in_buff_15, nullptr, tile_size_in_bytes);

    // Wait for kernels to complete
    run_mm2s_1.wait();
    std::cout << "mm2s_1 completed" << std::endl;
    run_mm2s_2.wait();
    std::cout << "mm2s_2 completed" << std::endl;
    run_mm2s_3.wait();
    std::cout << "mm2s_3 completed" << std::endl;
    run_mm2s_4.wait();
    std::cout << "mm2s_4 completed" << std::endl;
    run_mm2s_5.wait();
    std::cout << "mm2s_5 completed" << std::endl;
    run_mm2s_6.wait();
    std::cout << "mm2s_6 completed" << std::endl;
    run_mm2s_7.wait();
    std::cout << "mm2s_7 completed" << std::endl;
    run_mm2s_8.wait();
    std::cout << "mm2s_8 completed" << std::endl;
    run_mm2s_9.wait();
    std::cout << "mm2s_9 completed" << std::endl;
    run_mm2s_10.wait();
    std::cout << "mm2s_10 completed" << std::endl;
    run_mm2s_11.wait();
    std::cout << "mm2s_11 completed" << std::endl;
    run_mm2s_12.wait();
    std::cout << "mm2s_12 completed" << std::endl;
    run_mm2s_13.wait();
    std::cout << "mm2s_13 completed" << std::endl;
    run_mm2s_14.wait();
    std::cout << "mm2s_14 completed" << std::endl;
    run_mm2s_15.wait();
    std::cout << "mm2s_15 completed" << std::endl;

    run_s2mm_1.wait();
    std::cout << "s2mm_1 completed" << std::endl;
    run_s2mm_2.wait();
    std::cout << "s2mm_2 completed" << std::endl;
    run_s2mm_3.wait();
    std::cout << "s2mm_3 completed" << std::endl;
    run_s2mm_4.wait();
    std::cout << "s2mm_4 completed" << std::endl;
    run_s2mm_5.wait();
    std::cout << "s2mm_5 completed" << std::endl;
    run_s2mm_6.wait();
    std::cout << "s2mm_6 completed" << std::endl;
    run_s2mm_7.wait();
    std::cout << "s2mm_7 completed" << std::endl;
    run_s2mm_8.wait();
    std::cout << "s2mm_8 completed" << std::endl;
    run_s2mm_9.wait();
    std::cout << "s2mm_9 completed" << std::endl;
    run_s2mm_10.wait();
    std::cout << "s2mm_10 completed" << std::endl;
    run_s2mm_11.wait();
    std::cout << "s2mm_11 completed" << std::endl;
    run_s2mm_12.wait();
    std::cout << "s2mm_12 completed" << std::endl;
    run_s2mm_13.wait();
    std::cout << "s2mm_13 completed" << std::endl;
    run_s2mm_14.wait();
    std::cout << "s2mm_14 completed" << std::endl;
    run_s2mm_15.wait();
    std::cout << "s2mm_15 completed" << std::endl;

    auto run_sticker_mm2mm_1 = sticker_mm2mm_1<img_width, img_height, tile_width, data_width>(-----, img_out_buff, 0, 0);
    run_sticker_mm2mm_1.wait();

    for (unsigned i = 0; i < img_number; i++) {

        for (unsigned ti = 0; ti < tile_num_height; ti++) {
            for (unsigned tj = 0; tj < tile_num_width; tj++) {
                if (i == 0 && ti == 0 && tj ==0)
                    continue;
                unsigned aie_index = (ti * tile_num_width + tj) % aie_kernel_number;
                
                run_tile_mm2mm_1.set_arg(0, -----);
                run_tile_mm2mm_1.set_arg(2, tj);
                run_tile_mm2mm_1.set_arg(3, ti);
                run_tile_mm2mm_1.start();
                run_tile_mm2mm_1.wait();

            }
        }

    }


    // Synchronize the output buffer data from the device

    // Read output buffer data to local buffer
    // out_buff_1.read(DataOutput1);
    // out_buff_2.read(DataOutput2);
    // out_buff_3.read(DataOutput3);
    // out_buff_4.read(DataOutput4);
    // out_buff_5.read(DataOutput5);
    // out_buff_6.read(DataOutput6);
    // out_buff_7.read(DataOutput7);
    // out_buff_8.read(DataOutput8);
    // out_buff_9.read(DataOutput9);
    // out_buff_10.read(DataOutput10);
    // out_buff_11.read(DataOutput11);
    // out_buff_12.read(DataOutput12);
    // out_buff_13.read(DataOutput13);
    // out_buff_14.read(DataOutput14);
    // out_buff_15.read(DataOutput15);

    std::cout << "Writing data to output file" << std::endl;
    std::ofstream outputfile;
    outputfile.open("build.hw/aie_hw_run_data/output1.txt");
    for (unsigned i = 0; i < num_elements; i++) {
        outputfile << DataInput1[i] << std::endl;
    }
    outputfile.close();

    return 0;
}
