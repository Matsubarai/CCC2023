#include <iostream>
#include <fstream>
#include <random>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int* tile(int* input_buffer, int buffer_width, int buffer_height, int tile_width, int tile_height, int tile_x, int tile_y) {

    int tile_size = tile_width * tile_height;
    int* tile_buffer = (int*)malloc(sizeof(int) * tile_size);

    int x_offset = tile_x * (tile_width - 2);
    int y_offset = tile_y * (tile_height - 2);

    for (int i = 0; i < tile_height; i++) {
        for (int j = 0; j < tile_width; j++) {
            if ((i + y_offset < buffer_height) && (j + x_offset < buffer_width))
                tile_buffer[i * tile_width + j] = input_buffer[(i + y_offset) * buffer_width + j + x_offset];
            else if ((i + y_offset == buffer_height) && (j + x_offset < buffer_width))
                tile_buffer[i * tile_width + j] = input_buffer[(buffer_height - 1) * buffer_width + j + x_offset];
            else if ((i + y_offset < buffer_height) && (j + x_offset == buffer_width))
                tile_buffer[i * tile_width + j] = input_buffer[(i + y_offset) * buffer_width + buffer_width - 1];
            else if ((i + y_offset == buffer_height) && (j + x_offset == buffer_width))
                tile_buffer[i * tile_width + j] = input_buffer[(buffer_height - 1) * buffer_width + buffer_width - 1];
            else
                tile_buffer[i * tile_width + j] = 0;
        }
    }

    return tile_buffer;
}

// 采用 readme 中的 padding 方式，对整张图片进行计算，得到参考结果
void kernel_cal(int* kernel_buffer, int tile_width, int tile_height, int* kernel, int* kernel_out_buffer) {
    int Ptile_width = tile_width + 2;
    int Ptile_height = tile_height + 2;
    int Ptile_size = Ptile_width * Ptile_height;
    int* Pkernel = (int*)malloc(sizeof(int) * Ptile_size);


    // 对输入图片进行 padding
    for (int i = 0; i < tile_height; i++) {
        for (int j = 0; j < tile_width; j++) {
            Pkernel[(i + 1) * Ptile_width + (j + 1)] = kernel_buffer[i * tile_width + j];
        }
    }

    Pkernel[0] = Pkernel[Ptile_width + 1];
    Pkernel[Ptile_width - 1] = Pkernel[2 * Ptile_width - 2];
    Pkernel[(Ptile_height - 1) * Ptile_width] = Pkernel[(Ptile_height - 2) * Ptile_width + 1];
    Pkernel[Ptile_height * Ptile_width - 1] = Pkernel[(Ptile_height - 1) * Ptile_width - 2];
    for (int i = 1; i < Ptile_width - 1; i++) {
        Pkernel[i] = Pkernel[i + Ptile_width];
    }
    for (int i = 1; i < Ptile_height - 1; i++) {
        Pkernel[i * Ptile_width] = Pkernel[i * Ptile_width + 1];
        Pkernel[(i + 1) * Ptile_width - 1] = Pkernel[(i + 1) * Ptile_width - 2];
    }
    for (int i = 1; i < Ptile_width - 1; i++) {
        Pkernel[(Ptile_height - 1) * Ptile_width + i] = Pkernel[(Ptile_height - 2) * Ptile_width + i];
    }


    // 利用循环进行卷积运算
    int width_loop = Ptile_width - 2;
    int height_loop = Ptile_height - 2;
    for (int i = 0; i < height_loop; i++) {
        for (int j = 0; j < width_loop; j++) {
            kernel_out_buffer[i * tile_width + j] = 0;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    kernel_out_buffer[i * tile_width + j] += kernel[x * 3 + y] * Pkernel[(i + x) * Ptile_width + j + y];
                }
            }
        }
    }

	free(Pkernel);
}

void write_to_file(int array[], int size, const char filename[]) {
	std::ofstream outfile;
	outfile.open(filename);
	for (int i = 0; i < size; i++) {
		outfile << array[i] << std::endl;
	}
	outfile.close();
}


int main(int argc, char** argv) {

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

    // 卷积核的参数
	int kernel[9] = {64, 128, 64, 128, 256, 128, 64, 128, 64};

    // 一张输入图片采用 readme 中的分块算法所得：
    // 宽度维度上的分块个数
    // 高度维度上的分块个数
	int blk_num_width = ceil((float)(img_width - kernel_width) / (kernel_width - 2)) + 1;
	int blk_num_height = ceil((float)(img_height - kernel_height) / (kernel_height - 2)) + 1;

    // 用来存储输入的图片和对应的卷积参考结果
	int* img = new int[img_width * img_height];
	int* img_out_ref = new int[img_width * img_height];

    for (int n = 0; n < img_num; n++) {

        // 这里为了方便，直接通过代码来生成输入图片
        for (int i = 0; i < img_height * img_width; i++) {
            img[i] = i;
        }

        // 采用 readme 中的 padding 方式，对整张图片进行计算，得到参考结果
        kernel_cal(img, img_width, img_height, kernel, img_out_ref);

        write_to_file(img_out_ref, img_width * img_height, "ref.txt");

        // 对当前的图片进行分块操作，并依次存到对应 kernel 的输入文件中
        char file[100];
        for (int i = 0; i < blk_num_height; i++) {
            for (int j = 0; j < blk_num_width; j++) {

                int* blk = tile(img, img_width, img_height, kernel_width, kernel_height, j, i);

                sprintf(file, "./input%d.txt", (i * blk_num_width + j) % kernel_num + 1);

                write_to_file(blk, kernel_width * kernel_height, file);

                free(blk);
            }
        }

        // 当前图片的大小不一定能整除 kernel 的个数
        // 若不能整除，需要增加若干全零的分块到最后一组分块中
        int remain = (blk_num_height * blk_num_width) % kernel_num;

        if (remain != 0) {

            for (int i = 1; i <= kernel_num - remain; i++) {

                int* blk = (int*)calloc(kernel_width * kernel_height, sizeof(int));

                sprintf(file, "./input%d.txt", remain + i);

                write_to_file(blk, kernel_width * kernel_height, file);

                free(blk);
            }

        }
    }
	
	delete [] img;
	delete [] img_out_ref;

	return 0;
}
