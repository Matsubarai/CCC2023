#include <iostream>
#include <fstream>
#include <random>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void kernel_cal(int* kernel_buffer, int tile_width, int tile_height, int* kernel, int* kernel_out_buffer) {
    int Ptile_width = tile_width + 2;
    int Ptile_height = tile_height + 2;
    int Ptile_size = Ptile_width * Ptile_height;
    int* Pkernel = (int*)malloc(sizeof(int) * Ptile_size);

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

int main(int argc, char** argv) {

	int img_width = 1986;
	int img_height = 32;
	int blk_width = 64;
	int blk_height = 32;
	int kernel[9] = {64, 128, 64, 128, 256, 128, 64, 128, 64};

	int img_blk_width = ceil((float)(img_width - blk_width) / (blk_width - 2)) + 1;
	int img_blk_height = ceil((float)(img_height - blk_height) / (blk_height - 2)) + 1;

	int* img = new int[img_width*img_height];
	int* img_out_ref = new int[img_width*img_height];
	
	// int* blk = new int[blk_width*blk_height];

	std::string filename_prefix = "input";
	std::string filename_suffix = ".txt";

	// initialize img
	for (int i = 0; i < img_height*img_width; i++) {
		img[i] = i;
	}

	//void kernel_cal(int* kernel_buffer, int tile_width, int tile_height, int* kernel, int* kernel_out_buffer)
	kernel_cal(img, img_width, img_height, kernel, img_out_ref);

	write_to_file(img_out_ref, img_width*img_height, "ref.txt");

	// int* tile(int* input_buffer, int buffer_width, int buffer_height, int tile_width, int tile_height, int tile_x, int tile_y)

	char file[100];

	for (int i = 0; i < img_blk_height; i++) {
		for (int j = 0; j < img_blk_width; j++) {

			int* blk = tile(img, img_width, img_height, blk_width, blk_height, j, i);

			sprintf(file, "./input%d.txt", i * img_blk_width + j + 1);

			write_to_file(blk, blk_width*blk_height, file);

			free(blk);
		}
	}



	// int r, c;
	// for (r = 0; r < img_blk_height - 1; r++) {
	// 	for (c = 0; c < img_blk_width - 1; c++) {
	// 		for (int j = 0; j < blk_height; j++) {
	// 			memcpy(blk + j*blk_width, img + r*(blk_height-2)*img_width + j*img_width + c*(blk_width-2), (sizeof(int)) * blk_width);
	// 		}
	// 		write_to_file(blk, blk_width*blk_height, (filename_prefix + std::to_string(r*img_blk_height+c+1) + filename_suffix).c_str());
	// 	}
	// 	for (int j = 0; j < blk_height; j++) {
	// 		for (int k = 0; k < blk_width; k++) {
	// 			if (k < (img_width - (blk_width-2)*(img_blk_width-1)))
	// 				blk[j*blk_width + k] = img[r*(blk_height-2)*img_width + j*img_width + (blk_width-2)*(img_blk_width-1) + k];
	// 			else
	// 				blk[j*blk_width + k] = img[r*(blk_height-2)*img_width + (j+1)*img_width - 1];
	// 		}
	// 	}
	// 	write_to_file(blk, blk_width*blk_height, (filename_prefix + std::to_string(r*img_blk_height+c+1) + filename_suffix).c_str());
	// }

	// for (c = 0; c < img_blk_width - 1; c++) {
	// 	for (int j = 0; j < blk_height; j++) {
	// 		if (j < (img_height - (blk_height-2)*(img_blk_height-1))) {
	// 			memcpy(blk + j*blk_width, img + r*(blk_height-2)*img_width + j*img_width + c*(blk_width-2), (sizeof(int)) * blk_width);
	// 		}
	// 		else {
	// 			memcpy(blk + j*blk_width, img + (img_height-1)*img_width + c*(blk_width-2), (sizeof(int)) * blk_width);
	// 		}
	// 	}
	// 	write_to_file(blk, blk_width*blk_height, (filename_prefix + std::to_string(r*img_blk_height+c+1) + filename_suffix).c_str());
	// }

	// for (int j = 0; j < blk_height; j++) {
	// 	for (int k = 0; k < blk_width; k++) {
	// 		if (j < (img_height - (blk_height-2)*(img_blk_height-1)) && k < (img_width - (blk_width-2)*(img_blk_width-1)))
	// 			blk[j*blk_width + k] = img[r*(blk_height-2)*img_width + j*img_width + (blk_width-2)*(img_blk_width-1) + k];
	// 		else if (j < (img_height - (blk_height-2)*(img_blk_height-1)))
	// 			blk[j*blk_width + k] = img[r*(blk_height-2)*img_width + (j+1)*img_width - 1];
	// 		else if (k < (img_width - (blk_width-2)*(img_blk_width-1)))
	// 			blk[j*blk_width + k] = img[(img_height-1)*img_width + (blk_width-2)*(img_blk_width-1) + k];
	// 		else
	// 			blk[j*blk_width + k] = img[img_height*img_width-1];
	// 	}
	// }

	// write_to_file(blk, blk_width*blk_height, (filename_prefix + std::to_string(r*img_blk_height+c+1) + filename_suffix).c_str());
	
	delete [] img;
	// delete [] blk;
	delete [] img_out_ref;

	return 0;
}
