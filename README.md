# CCFSys 2023

> University：University of Science and Technology of China
> 
> Mentor：Chao Wang
> 
> Team：ZhenDong Zheng, BinZe Jiang, QianYu Cheng


 ## Problem

- Basic - Vision 3X3 filter2D on 64x64 image

  Create the filter2D function with 3x3 kernel on 64x64 image using AIE API or AIE Intrinsic based on personal understanding

	- AIE Emulation succeeded
	- The design report submitted

- Advanced - Image Signal Processing Pipeline on HD image

  Create high definition image processing pipeline design based on personal understanding. It is encouraged to fully use the Vitis Vision Library.

	- The system level emulation or the hardware run on VCK5000 succeeded
	- The design report submitted

## Performance Analyzer

We tested the platform using randomly generated 32-bit matrix data, batching 100 images. Experimental data shows that the average processing time of a single 4K resolution data is 87ms, and the processing frame rate is 11.42fps. Among them, the delay of data transfer in and out is 24.63ms, which is close to half of the total time, indicating that the computing overhead has not affected the overall performance of the system, and the bottleneck of running the two-dimensional convolution algorithm mainly lies in memory fetching.


## Design Report

- Report：[Report](https://github.com/abuqiqi/CCC2023/blob/main/%E8%AE%BE%E8%AE%A1%E6%8A%A5%E5%91%8A.pdf)

## Excution

Take the 'filter2D' project submitted in the 'sources' folder of this repository as an example, you can perform AIE simulation and hardware run.

1. AIE simulation

   Execute the following code to run the simulation of AIE separately.

```shell
# Compile and run the AIE simulation
cd ./CCC2023/sources/filter2D/aie
make
make aieemu
```

2. Hardware run

   Run on the HAC NUX

   Under the 'sources/filter2D/execution' folder, the necessary 'fft.xclbin' file and 'host.exe' file are stored to call PL and AIE through the host. To run on the VCK5000, execute the following code.

```shell
# Clone the repository
git clone https://github.com/Xtra-Computing/hacc_demo.git

# Obtain VCK5000 compute nodes (modify instructions based on hacc_demo storage path)
./hacc_demo/env/vck5000_alloc 3
source ./hacc_demo/env/vck5000_env

# Run the executable in the execution folder of this project
./CCC2023/sources/filter2D/execution/host.exe

# Exit the node
./hacc_demo/env/vck5000_exit
```

## Repository tree
The main directory structure of this repository is as follows
```
CCC2023
├── sources
│   ├── filter2D
│       ├── aie
│       ├── execution
│       ├── host
│       ├── hw_link
│       ├── notebook
│       ├── pl
│       └── Makefile
│
├── README.md
└── Report.pdf
```

## Reference
