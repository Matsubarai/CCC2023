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
    auto mm2s_1 = xrt::kernel(device, uuid, "mm2s:{mm2s1}");
    auto mm2s_2 = xrt::kernel(device, uuid, "mm2s:{mm2s2}");
    auto mm2s_3 = xrt::kernel(device, uuid, "mm2s:{mm2s3}");
    auto mm2s_4 = xrt::kernel(device, uuid, "mm2s:{mm2s4}");
    auto mm2s_5 = xrt::kernel(device, uuid, "mm2s:{mm2s5}");
    auto mm2s_6 = xrt::kernel(device, uuid, "mm2s:{mm2s6}");
    auto mm2s_7 = xrt::kernel(device, uuid, "mm2s:{mm2s7}");
    auto mm2s_8 = xrt::kernel(device, uuid, "mm2s:{mm2s8}");
    auto mm2s_9 = xrt::kernel(device, uuid, "mm2s:{mm2s9}");
    auto mm2s_10 = xrt::kernel(device, uuid, "mm2s:{mm2s10}");
    auto mm2s_11 = xrt::kernel(device, uuid, "mm2s:{mm2s11}");
    auto mm2s_12 = xrt::kernel(device, uuid, "mm2s:{mm2s12}");
    auto mm2s_13 = xrt::kernel(device, uuid, "mm2s:{mm2s13}");
    auto mm2s_14 = xrt::kernel(device, uuid, "mm2s:{mm2s14}");
    auto mm2s_15 = xrt::kernel(device, uuid, "mm2s:{mm2s15}");

    auto s2mm_1 = xrt::kernel(device, uuid, "s2mm:{s2mm1}");
    auto s2mm_2 = xrt::kernel(device, uuid, "s2mm:{s2mm2}");
    auto s2mm_3 = xrt::kernel(device, uuid, "s2mm:{s2mm3}");
    auto s2mm_4 = xrt::kernel(device, uuid, "s2mm:{s2mm4}");
    auto s2mm_5 = xrt::kernel(device, uuid, "s2mm:{s2mm5}");
    auto s2mm_6 = xrt::kernel(device, uuid, "s2mm:{s2mm6}");
    auto s2mm_7 = xrt::kernel(device, uuid, "s2mm:{s2mm7}");
    auto s2mm_8 = xrt::kernel(device, uuid, "s2mm:{s2mm8}");
    auto s2mm_9 = xrt::kernel(device, uuid, "s2mm:{s2mm9}");
    auto s2mm_10 = xrt::kernel(device, uuid, "s2mm:{s2mm10}");
    auto s2mm_11 = xrt::kernel(device, uuid, "s2mm:{s2mm11}");
    auto s2mm_12 = xrt::kernel(device, uuid, "s2mm:{s2mm12}");
    auto s2mm_13 = xrt::kernel(device, uuid, "s2mm:{s2mm13}");
    auto s2mm_14 = xrt::kernel(device, uuid, "s2mm:{s2mm14}");
    auto s2mm_15 = xrt::kernel(device, uuid, "s2mm:{s2mm15}");

    // Allocating the input size of sizeIn to MM2S
    std::cout << "Allocate Buffer in Global Memory" << std::endl;
    unsigned num_elements = 573440;
    size_t size_in_bytes = sizeof(int) * num_elements;
    auto in_buff_1 = xrt::bo(device, size_in_bytes, mm2s_1.group_id(0));
    auto in_buff_2 = xrt::bo(device, size_in_bytes, mm2s_2.group_id(0));
    auto in_buff_3 = xrt::bo(device, size_in_bytes, mm2s_3.group_id(0));
    auto in_buff_4 = xrt::bo(device, size_in_bytes, mm2s_4.group_id(0));
    auto in_buff_5 = xrt::bo(device, size_in_bytes, mm2s_5.group_id(0));
    auto in_buff_6 = xrt::bo(device, size_in_bytes, mm2s_6.group_id(0));
    auto in_buff_7 = xrt::bo(device, size_in_bytes, mm2s_7.group_id(0));
    auto in_buff_8 = xrt::bo(device, size_in_bytes, mm2s_8.group_id(0));
    auto in_buff_9 = xrt::bo(device, size_in_bytes, mm2s_9.group_id(0));
    auto in_buff_10 = xrt::bo(device, size_in_bytes, mm2s_10.group_id(0));
    auto in_buff_11 = xrt::bo(device, size_in_bytes, mm2s_11.group_id(0));
    auto in_buff_12 = xrt::bo(device, size_in_bytes, mm2s_12.group_id(0));
    auto in_buff_13 = xrt::bo(device, size_in_bytes, mm2s_13.group_id(0));
    auto in_buff_14 = xrt::bo(device, size_in_bytes, mm2s_14.group_id(0));
    auto in_buff_15 = xrt::bo(device, size_in_bytes, mm2s_15.group_id(0));

    auto out_buff_1 = xrt::bo(device, size_in_bytes, s2mm_1.group_id(0));
    auto out_buff_2 = xrt::bo(device, size_in_bytes, s2mm_2.group_id(0));
    auto out_buff_3 = xrt::bo(device, size_in_bytes, s2mm_3.group_id(0));
    auto out_buff_4 = xrt::bo(device, size_in_bytes, s2mm_4.group_id(0));
    auto out_buff_5 = xrt::bo(device, size_in_bytes, s2mm_5.group_id(0));
    auto out_buff_6 = xrt::bo(device, size_in_bytes, s2mm_6.group_id(0));
    auto out_buff_7 = xrt::bo(device, size_in_bytes, s2mm_7.group_id(0));
    auto out_buff_8 = xrt::bo(device, size_in_bytes, s2mm_8.group_id(0));
    auto out_buff_9 = xrt::bo(device, size_in_bytes, s2mm_9.group_id(0));
    auto out_buff_10 = xrt::bo(device, size_in_bytes, s2mm_10.group_id(0));
    auto out_buff_11 = xrt::bo(device, size_in_bytes, s2mm_11.group_id(0));
    auto out_buff_12 = xrt::bo(device, size_in_bytes, s2mm_12.group_id(0));
    auto out_buff_13 = xrt::bo(device, size_in_bytes, s2mm_13.group_id(0));
    auto out_buff_14 = xrt::bo(device, size_in_bytes, s2mm_14.group_id(0));
    auto out_buff_15 = xrt::bo(device, size_in_bytes, s2mm_15.group_id(0));

    // Read data from file 
    auto *DataInput1 = new int [num_elements];
    auto *DataInput2 = new int [num_elements];
    auto *DataInput3 = new int [num_elements];
    auto *DataInput4 = new int [num_elements];
    auto *DataInput5 = new int [num_elements];
    auto *DataInput6 = new int [num_elements];
    auto *DataInput7 = new int [num_elements];
    auto *DataInput8 = new int [num_elements];
    auto *DataInput9 = new int [num_elements];
    auto *DataInput10 = new int [num_elements];
    auto *DataInput11 = new int [num_elements];
    auto *DataInput12 = new int [num_elements];
    auto *DataInput13 = new int [num_elements];
    auto *DataInput14 = new int [num_elements];
    auto *DataInput15 = new int [num_elements];

    auto *DataOutput1 = new int [num_elements];
    auto *DataOutput2 = new int [num_elements];
    auto *DataOutput3 = new int [num_elements];
    auto *DataOutput4 = new int [num_elements];
    auto *DataOutput5 = new int [num_elements];
    auto *DataOutput6 = new int [num_elements];
    auto *DataOutput7 = new int [num_elements];
    auto *DataOutput8 = new int [num_elements];
    auto *DataOutput9 = new int [num_elements];
    auto *DataOutput10 = new int [num_elements];
    auto *DataOutput11 = new int [num_elements];
    auto *DataOutput12 = new int [num_elements];
    auto *DataOutput13 = new int [num_elements];
    auto *DataOutput14 = new int [num_elements];
    auto *DataOutput15 = new int [num_elements];

    for (unsigned int i = 0; i < num_elements; i++) {
        DataInput1[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput2[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput3[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput4[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput5[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput6[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput7[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput8[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput9[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput10[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput11[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput12[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput13[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput14[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
        DataInput15[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
    }

    in_buff_1.write(DataInput1);
    in_buff_2.write(DataInput2);
    in_buff_3.write(DataInput3);
    in_buff_4.write(DataInput4);
    in_buff_5.write(DataInput5);
    in_buff_6.write(DataInput6);
    in_buff_7.write(DataInput7);
    in_buff_8.write(DataInput8);
    in_buff_9.write(DataInput9);
    in_buff_10.write(DataInput10);
    in_buff_11.write(DataInput11);
    in_buff_12.write(DataInput12);
    in_buff_13.write(DataInput13);
    in_buff_14.write(DataInput14);
    in_buff_15.write(DataInput15);

    // Synchronize input buffers data to device global memory
    std::cout << "Synchronize input buffers data to device global memory" << std::endl;
    in_buff_1.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_2.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_3.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_4.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_5.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_6.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_7.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_8.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_9.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_10.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_11.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_12.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_13.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_14.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_15.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    // Execute the compute units
    std::cout << "Run the kernels" << std::endl;
    auto run_s2mm_1 = s2mm_1(out_buff_1, nullptr, size_in_bytes);
    auto run_s2mm_2 = s2mm_2(out_buff_2, nullptr, size_in_bytes);
    auto run_s2mm_3 = s2mm_3(out_buff_3, nullptr, size_in_bytes);
    auto run_s2mm_4 = s2mm_4(out_buff_4, nullptr, size_in_bytes);
    auto run_s2mm_5 = s2mm_5(out_buff_5, nullptr, size_in_bytes);
    auto run_s2mm_6 = s2mm_6(out_buff_6, nullptr, size_in_bytes);
    auto run_s2mm_7 = s2mm_7(out_buff_7, nullptr, size_in_bytes);
    auto run_s2mm_8 = s2mm_8(out_buff_8, nullptr, size_in_bytes);
    auto run_s2mm_9 = s2mm_9(out_buff_9, nullptr, size_in_bytes);
    auto run_s2mm_10 = s2mm_10(out_buff_10, nullptr, size_in_bytes);
    auto run_s2mm_11 = s2mm_11(out_buff_11, nullptr, size_in_bytes);
    auto run_s2mm_12 = s2mm_12(out_buff_12, nullptr, size_in_bytes);
    auto run_s2mm_13 = s2mm_13(out_buff_13, nullptr, size_in_bytes);
    auto run_s2mm_14 = s2mm_14(out_buff_14, nullptr, size_in_bytes);
    auto run_s2mm_15 = s2mm_15(out_buff_15, nullptr, size_in_bytes);
    auto run_mm2s_1 = mm2s_1(in_buff_1, nullptr, size_in_bytes);
    auto run_mm2s_2 = mm2s_2(in_buff_2, nullptr, size_in_bytes);
    auto run_mm2s_3 = mm2s_3(in_buff_3, nullptr, size_in_bytes);
    auto run_mm2s_4 = mm2s_4(in_buff_4, nullptr, size_in_bytes);
    auto run_mm2s_5 = mm2s_5(in_buff_5, nullptr, size_in_bytes);
    auto run_mm2s_6 = mm2s_6(in_buff_6, nullptr, size_in_bytes);
    auto run_mm2s_7 = mm2s_7(in_buff_7, nullptr, size_in_bytes);
    auto run_mm2s_8 = mm2s_8(in_buff_8, nullptr, size_in_bytes);
    auto run_mm2s_9 = mm2s_9(in_buff_9, nullptr, size_in_bytes);
    auto run_mm2s_10 = mm2s_10(in_buff_10, nullptr, size_in_bytes);
    auto run_mm2s_11 = mm2s_11(in_buff_11, nullptr, size_in_bytes);
    auto run_mm2s_12 = mm2s_12(in_buff_12, nullptr, size_in_bytes);
    auto run_mm2s_13 = mm2s_13(in_buff_13, nullptr, size_in_bytes);
    auto run_mm2s_14 = mm2s_14(in_buff_14, nullptr, size_in_bytes);
    auto run_mm2s_15 = mm2s_15(in_buff_15, nullptr, size_in_bytes);

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

    // Synchronize the output buffer data from the device
    out_buff_1.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_2.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_3.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_4.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_5.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_6.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_7.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_8.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_9.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_10.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_11.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_12.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_13.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_14.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_15.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

    // Read output buffer data to local buffer
    out_buff_1.read(DataOutput1);
    out_buff_2.read(DataOutput2);
    out_buff_3.read(DataOutput3);
    out_buff_4.read(DataOutput4);
    out_buff_5.read(DataOutput5);
    out_buff_6.read(DataOutput6);
    out_buff_7.read(DataOutput7);
    out_buff_8.read(DataOutput8);
    out_buff_9.read(DataOutput9);
    out_buff_10.read(DataOutput10);
    out_buff_11.read(DataOutput11);
    out_buff_12.read(DataOutput12);
    out_buff_13.read(DataOutput13);
    out_buff_14.read(DataOutput14);
    out_buff_15.read(DataOutput15);

    std::cout << "Writing data to output file" << std::endl;
    std::ofstream outputfile;
    outputfile.open("build.hw/aie_hw_run_data/output1.txt");
    for (unsigned i = 0; i < num_elements; i++) {
        outputfile << DataInput1[i] << std::endl;
    }
    outputfile.close();

    return 0;
}
