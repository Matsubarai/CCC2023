#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

void sticker(int* tile_buffer, int tile_width, int tile_height, int tile_x, int tile_y, int* output_buffer, int buffer_width, int buffer_height) {

    int x_tile_num = ceil((float)(buffer_width - tile_width) / (tile_width - 2)) + 1;
    int y_tile_num = ceil((float)(buffer_height - tile_height) / (tile_height - 2)) + 1;

    int x_offset;
    int y_offset;

    if (tile_y == 0 && tile_x == 0) {
        for (int i = 0; i < tile_height; i++) {
            for (int j = 0; j < tile_width; j++) {
                output_buffer[i * buffer_width + j] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_y == 0 && tile_x > 0 && tile_x <= x_tile_num - 2) {
        x_offset = tile_x * (tile_width - 2) + 1;
        for (int i = 0; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                output_buffer[i * buffer_width + j  - 1 + x_offset] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_x == 0 && tile_y > 0 && tile_y <= y_tile_num - 2) {
        y_offset = tile_y * (tile_height - 2) + 1;
        for (int i = 1; i < tile_height; i++) {
            for (int j = 0; j < tile_width; j++) {
                output_buffer[(i - 1 + y_offset) * buffer_width + j] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_x > 0 && tile_y > 0 && tile_x <= x_tile_num - 2 && tile_y <= y_tile_num - 2) {
        y_offset = tile_y * (tile_height - 2) + 1;
        x_offset = tile_x * (tile_width - 2) + 1;
        for (int i = 1; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                output_buffer[(i - 1 + y_offset) * buffer_width + j - 1 + x_offset] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_y == 0 && tile_x == x_tile_num - 1) {
        x_offset = tile_x * (tile_width - 2) + 1;
        for (int i = 0; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                if (j - 1 + x_offset < buffer_width)
                    output_buffer[i * buffer_width + j - 1 + x_offset] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_y > 0 && tile_y <= y_tile_num - 2 && tile_x == x_tile_num - 1) {
        x_offset = tile_x * (tile_width - 2) + 1;
        y_offset = tile_y * (tile_height - 2) + 1;
        for (int i = 1; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                if (j  - 1 + x_offset < buffer_width)
                    output_buffer[(i - 1 + y_offset) * buffer_width + j - 1 + x_offset] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_x == 0 && tile_y == y_tile_num - 1) {
        y_offset = tile_y * (tile_height - 2) + 1;
        for (int i = 1; i < tile_height; i++) {
            for (int j = 0; j < tile_width; j++) {
                if (i - 1 + y_offset < buffer_height)
                    output_buffer[(i - 1 + y_offset) * buffer_width + j] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_y == y_tile_num - 1 && tile_x > 0 && tile_x <= x_tile_num - 2) {
        x_offset = tile_x * (tile_width - 2) + 1;
        y_offset = tile_y * (tile_height - 2) + 1;
        for (int i = 1; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                if (i + y_offset - 1< buffer_height)
                    output_buffer[(i - 1 + y_offset) * buffer_width + j - 1 + x_offset] = tile_buffer[i * tile_width + j];
            }
        }
    }

    if (tile_y == y_tile_num - 1 && tile_x == x_tile_num - 1) {
        x_offset = tile_x * (tile_width - 2) + 1;
        y_offset = tile_y * (tile_height - 2) + 1;
        for (int i = 1; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                if ((i - 1 + y_offset < buffer_height) && (j - 1 + x_offset < buffer_width))
                    output_buffer[(i - 1 + y_offset) * buffer_width + j - 1 + x_offset] = tile_buffer[i * tile_width + j];
            }
        }
    }
}

void read_to_mem(int data[], int size, const char filename[], int file_offset) {
	fstream ioFile;
	ioFile.open(filename, ios::in);
    if (!ioFile) {
        cout << filename << "cannot open" << endl;
        exit(0);
    }

    ioFile.seekg(file_offset, ios::beg);
	for (int i = 0; i < size; i++) {
		std::string num;
		getline(ioFile, num);
		while (num.c_str()[0] == 'T')
			getline(ioFile, num);
		data[i] = stoi(num);
	}
	ioFile.close();
}


int main(int argc, char** argv) {
    // 卷积结果参考文件
    char ref_file[100] = "./ref.txt";

    // 输入图片的张数（此处默认图片只有一维）
    // 输入图片的宽度
    // 输入图片的高度
    int img_num = 2;
    int img_width = 3840;
    int img_height = 2160;

    // AIE kernel 的个数
    // 一个 AIE kernel 能处理的图片宽度
    // 一个 AIE kernel 能处理的图片高度
    int kernel_num = 32;
    int kernel_width = 64;
    int kernel_height = 32;
    
    // 用来存储拼接好的利用 AIE 计算的结果
    int* img_out;
    // 参考结果
    int* img_out_ref;
    // 暂存一个 AIE kernel 的计算结果 
    int* blk_out;

    img_out = (int *)malloc(sizeof(int) * img_width * img_height);
    img_out_ref = (int *)malloc(sizeof(int) * img_width * img_height);
    blk_out = (int *)malloc(sizeof(int) * kernel_width * kernel_height);

    char file[100];
    int file_offset;

    // 一张输入图片采用 readme 中的分块算法所得：
    // 宽度维度上的分块个数
    // 高度维度上的分块个数
    int blk_num_width = ceil((float)(img_width - kernel_width) / (kernel_width - 2)) + 1;
    int blk_num_height = ceil((float)(img_height - kernel_height) / (kernel_height - 2)) + 1;
    
    for (int n = 0; n < img_num; n++) {

        // 拼接出当前图片的计算结果

        // 当前图片的大小不一定能整除 kernel 的个数
        // 若不能整除，若不能整除，在最后一组kernel计算的结果中，输入为零的那些分块对应的结果应该全部跳过
        // 这里通过 file_offset 已经考虑了这种情况
        for (int i = 0; i < blk_num_height; i++) {
            for (int j = 0; j < blk_num_width; j++) {
                
                // 读出当前分块的数据
                sprintf(file, "../Emulation-AIE/aiesimulator_output/data/output%d.txt", (i * blk_num_width + j) % kernel_num + 1);
                file_offset = 2 * ((i * blk_num_width + j) / kernel_num) * kernel_width * kernel_height + 
                                n * 2 * ceil((float)(blk_num_height * blk_num_width) / kernel_num) * kernel_width * kernel_height;
                read_to_mem(blk_out, kernel_width * kernel_height, file, file_offset);

                // 将当前分块结果拼接到最终输出中
                sticker(blk_out, kernel_width, kernel_height, j, i, img_out, img_width, img_height);

            }
        }

        // 读出当前文件的参考结果
        file_offset = n * img_width * img_height;
        read_to_mem(img_out_ref, img_height * img_width, ref_file, file_offset);

        // 使 AIE 结果与参考结果进行对比
        int erro = 0;
        for (int i = 0; i < img_height; i++) {
            for (int j = 0; j < img_width; j++) {
                if (abs(img_out[i * img_width + j] - img_out_ref[i * img_width + j]) > 1e-3) {
                    erro++;
                }
            }
        }
        printf("No.%d fig erro time:%d\n", (n + 1), erro);
    }
    
    free(img_out);
    free(img_out_ref);
    free(blk_out);
}
