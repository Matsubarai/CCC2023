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




## Design Report

- Report：[Report](https://github.com/abuqiqi/CCC2023/blob/main/%E8%AE%BE%E8%AE%A1%E6%8A%A5%E5%91%8A.pdf)

## Excution

Take the 'filter2D' project submitted in the 'sources' folder of this repository as an example, you can perform AIE simulation and hardware run.

1. AIE simulation

Execute the following code to run the simulation of AIE separately.

```shell
# Compile and run the AIE simulation
cd ./CCC2023/sources/fft_4k/aie
make
make aieemu
```

2. Hardware run

	 Run on the HAC NUX
在`sources/fft_4k/execution`文件夹下存放了通过主机调用PL和AIE必要的`fft.xclbin`文件、`host.exe`文件和输入文件`DataInFFTO.txt`，以及运行完毕所产生的输出文件`DataOutFFT0.txt`。如需在VCK5000上运行，可执行以下代码。

```shell
# 克隆hacc_demo仓库
git clone https://github.com/Xtra-Computing/hacc_demo.git

# 获取VCK5000计算节点（根据hacc_demo存放路径修改指令）
./hacc_demo/env/vck5000_alloc 3
source ./hacc_demo/env/vck5000_env

# 在本项目的execution文件夹下运行可执行文件
./CCC2023/sources/fft_4k/execution/host.exe

# 退出节点
./hacc_demo/env/vck5000_exit
```

执行完毕后，可使用`sources/fft_4k/notebook`文件夹下的`.ipynb`文件可视化输出结果并进行验证。

## Repository tree
本仓库的主要目录结构如下。
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
└── 设计报告.pdf
```

## Reference
