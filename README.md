# 实验报告

## 选题
Filter2D

## 摘要
本实验总的设计思路是让每个AIE复用[Xilinx官方的filter2D API](https://github.com/Xilinx/Vitis_Libraries/blob/2022.2/vision/L1/include/aie/imgproc/xf_filter2d_16b_aie.hpp)，使得每个AIE能够对固定大小的图片进行卷积操作。然后利用PL端对输入的任意大小的图片进行[分块操作](https://github.com/DongDongZZD/CCC2023)，分块后的矩阵大小与每个AIE能处理的图片大小相同。之后调用一组AIE循环对这些分块数据进行处理，最后再利用PL端将计算好的分块数据进行[拼接操作](https://github.com/DongDongZZD/CCC2023)即可。这里输入图片的大小需不小于每个AIE能处理的图片大小，另外重复进行上述过程即可处理多张图片。
但由于host端代码始终运行有误等若干原因，本实验仅进行了仿真。即需手动调用[分块操作](https://github.com/DongDongZZD/CCC2023)代码对图片进行分块，得到若干输入文件，然后再通过仿真调用AIE得到若干输出文件，最后运行[拼接操作](https://github.com/DongDongZZD/CCC2023)代码得到卷积后的结果。

## 系统设计

### AIE代码

本设计的AIE代码直接利用了[已有API](https://github.com/Xilinx/Vitis_Libraries/blob/2022.2/vision/L1/include/aie/imgproc/xf_filter2d_16b_aie.hpp)，细节不做过多赘述。
唯一的区别在于，为了能处理64*64的矩阵，需要对代码中矩阵大小的参数进行相应修改。

### 对数据进行分块以及拼接

因为未找到可适配x86平台的矩阵 tile & sticker API，本实验对 tile & sticker 代码进行了复现

需注意这里的 padding 操作采取了[filter2D API](https://github.com/Xilinx/Vitis_Libraries/blob/2022.2/vision/L1/include/aie/imgproc/xf_filter2d_16b_aie.hpp)中的做法，即：
- padding 后矩阵四个角的数据与原矩阵四个角的数据相同
- padding 后矩阵第一列/行的数据与原矩阵第一列/行的数据相同
- padding 后矩阵最后一列/行的数据与原矩阵最后一列/行的数据相同

另外卷积核的步长固定为 1

#### 分块
分块的重点是需要处理相邻分块矩阵数据的 overlap，根据 padding 策略和卷积核的步长，这里的 overlap 策略为：
- 左右两个分块矩阵需要重叠左侧矩阵的最后两列数据，如图1所示
![图1 左右分块矩阵的 overlap](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/1.png)

- 上下两个分块矩阵需要重叠上方矩阵的最后两行数据，如图2所示



### Graph

## 系统测试

## 结论
