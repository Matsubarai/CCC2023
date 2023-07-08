#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

void read_to_mem(int data[], int size, const char filename[]) {
	std::ifstream infile;
	infile.open(filename);

	for (int i = 0; i < size; i++) {
		std::string num;
		getline(infile, num);
		while (num.c_str()[0] == 'T')
			getline(infile, num);
		data[i] = stoi(num);
	}
	infile.close();
}

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



int main(int argc, char** argv) {
    FILE *fin;
    char file[100];

    int image_width = 1986;
    int image_height = 32;
    int tile_width = 64;
    int tile_height = 32;

    int* image_out;
    int* image_out_ref;
    int* tile_out;

    char*  tmp;

    image_out = (int *)malloc(sizeof(int) * image_width * image_height);
    image_out_ref = (int *)malloc(sizeof(int) * image_width * image_height);
    tile_out = (int *)malloc(sizeof(int) * tile_width * tile_height);

    int tile_x_num = ceil((float)(image_width - tile_width) / (tile_width - 2)) + 1;
    int tile_y_num = ceil((float)(image_height - tile_height) / (tile_height - 2)) + 1;

    for (int i = 0; i < tile_y_num; i++) {
        for (int j = 0; j < tile_x_num; j++) {


            sprintf(file, "../Emulation-AIE/aiesimulator_output/data/output%d.txt", (i * tile_x_num) + j+1);
            if ((fin = fopen(file, "r")) == NULL) {
                printf("image file can not find\n");
                exit(0);
            }

            // read_to_mem(int data[], int size, const char filename[])
            read_to_mem(tile_out, tile_width*tile_height, file);
            // for (int y = 0; y < tile_height; y++) {
            //     for (int x = 0; x < tile_width; x++) {
            //         // fscanf(fin, "%[^\n]", tmp);
            //         size_t len;
            //         getline(&tmp, &len, fin);

            //         if (y == (tile_height - 1) && (x == tile_width - 1)) {
            //             // fscanf(fin, "%[^\n]", tmp);
            //             getline(&tmp, &len, fin);
            //         }

            //         fscanf(fin, "%d", &tile_out[y * tile_width + x]);
            //     }
            // }

            // void sticker(int* tile_buffer, int tile_width, int tile_height, int tile_x, int tile_y, int* output_buffer, int buffer_width, int buffer_height) 
            sticker(tile_out, tile_width, tile_height, j, i, image_out, image_width, image_height);

            fclose(fin);

        }
    }

    if ((fin = fopen("./ref.txt", "r")) == NULL) {
        printf("image file can not find\n");
        exit(0);
    }

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            fscanf(fin, "%d", &image_out_ref[i*image_width + j]);
        }
    }

    int erro = 0;
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            if (abs(image_out[i * image_width + j] - image_out_ref[i * image_width + j]) > 1e-3) {
                //printf("erro x:%d  erro y:%d\n", j, i);
                erro++;
            }
        }
    }
    printf("erro time:%d\n", erro);
    
    fclose(fin);
    free(tmp);
    free(image_out);
    free(image_out_ref);
    free(tile_out);
}