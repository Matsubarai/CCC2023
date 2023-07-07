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
[分块](https://github.com/Xilinx/Vitis_Libraries/blob/2022.2/vision/L1/include/aie/imgproc/xf_filter2d_16b_aie.hp)的重点是需要处理相邻分块矩阵数据的 overlap，根据 padding 策略和卷积核的步长，这里的 overlap 策略为：
- 左右两个分块矩阵需要重叠左侧矩阵的最后两列数据，如图1所示
![图1](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/1.png "图1 左右分块矩阵的 overlap")
- 上下两个分块矩阵需要重叠上方矩阵的最后两行数据，如图2所示
![图2](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/2.png "图2 上下分块矩阵的 overlap")

完整图片的分块示意图如下，截取每个分块数据的关键就在于获得这个分块相对于原点的偏移
![图3](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/3.png "图3 分块的示意图")

另外对于最后一行和最后一列的分块，它们涵盖的范围有部分是超过了原始图片区域。根据 padding 策略，只需将原始图片的最后一行/列的数据复制给这部分区域的第一行/列即可，如下图所示
![图4](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/4.png "图4 特殊分块示意图")

#### 拼接

AIE会对每个分块数据进行 padding 后再卷积，因此AIE计算所得的部分分块结果在拼接时需要丢弃。这里的算法将计算所得的各个分块数据按照其在原始图片中的顺序进行拼接（从左至右，从上至下），具体算法描述如下：

- 位于左上角的分块，其最后一列和最后一行的计算结果是错误的（除了完整图片的大小和AIE能处理的图片大小一致等特殊情况）。如下图所示，粉色区域代表AIE进行 padding 后得到的数据，红色区域代表错误的结果。但是为了满足 完整图片大小与AIE能处理的图片大小一致 等特殊情况，这里直接将这个分块所有的计算结果都写入最终输出中。这样最终输出中并不会包含这些错误的数据，因为按照从左至右，从上至下对分块结果进行拼接时，后续的分块会用正确的结果覆盖掉这些错误数据。
![图5](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/5.png "图5 左上角分块的完整历程")
- 右上角分块的处理方式如下图所示，此分块的一部分数据不属于原始图片。绿色区域数据是属于原始图片的，蓝色区域数据与原始图片最后一列的数据相同，粉色和红色区域与之前的描述一致。这里写回时，依然会将最后一列没有超过原始图片区域的数据写入最终结果中，因为后续的分块会用正确的结果覆盖掉错误的数据。
![图6](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/6.png "图6 左上角分块的完整历程")
- 右下角和右上角分块的处理方式都类似，分别如下图所示
![图7](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/7.png "图7 左上角分块的完整历程")
![图8](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/8.png "图8 左上角分块的完整历程")

- 位于第一列（除左上角和左下角）的分块，其第一行、最后一行和最后一列的计算结果是错误的。但是这里依然会将此分块最后一列和最后一行的数据写入最终结果中，同样因为后续的分块会用正确的结果覆盖掉这些错误数据。
![图9](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/9.png "图9 第一列分块的完整历程")
- 位于第一行（除左上角和右上角）的分块类似，如下图所示
![图10](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/10.png "图10 第一行分块的完整历程")
- 位于最后一列和最后一行（除左下角、右下角和右上角）的分块与右上角分块的处理方式类似，这些分块的一部分数据不属于原始图片，其处理方式分别如下图所示
![图11](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/11.png "图11 第一行分块的完整历程")
![图12](https://github.com/DongDongZZD/CCC2023/blob/main/readme_image/12.png "图12 第一行分块的完整历程")




### Graph

## 系统测试

## 结论
