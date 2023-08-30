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

- Report：[Report](./report.pdf)

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

   Run on the HACC NUS

```shell
# Clone the repository
git clone https://github.com/Xtra-Computing/hacc_demo.git
git clone https://github.com/Matsubarai/CCC2023.git

# Obtain VCK5000 compute nodes (modify instructions based on hacc_demo storage path)
./hacc_demo/env/vck5000_alloc 3
source ./hacc_demo/env/vck5000_env

# Run
cd CCC2023/source/filter2D
make
make run <IMG_NUM>

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
|       ├── build.hw
│       ├── host
│       ├── hw_link
│       ├── pl
│       └── Makefile
│
├── README.md
└── Report.pdf
```

## Reference
