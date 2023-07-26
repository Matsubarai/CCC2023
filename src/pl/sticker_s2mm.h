#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>





// 将当前横纵坐标对应的 tile 拼接到图片中
template <unsigned img_width, unsigned img_height, unsigned tile_width, unsigned tile_height, 
unsgined tile_index_width, unsigned tile_index_height, unsigned data_width>
void sticker(ap_int<data_width> *mem, hls::stream<qdma_axis<data_width, 0, 0, 0>> &stream) {

    using data = qdma_axis<data_width, 0, 0, 0>;

    unsigned tile_num_width  = ceil((float)(img_width - tile_width) / (tile_width - 2)) + 1;
    unsigned tile_num_height = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

    unsigned offset_width  = tile_index_width * (tile_width - 2);
    unsigned offset_height = tile_index_height * (tile_height - 2);

    unsigned index;

    if (tile_index_height == 0 && tile_index_width == 0) {
        for (int i = 0; i < tile_height - 1; i++) {
            for (int j = 0; j < tile_width - 1; j++) {

                index = (i + offset_height) * img_width + j + offset_width;
                data x = stream.read();
                mem[index] = x.get_data();

            }
        }
    }

    if (tile_index_height == 0 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
        for (int i = 0; i < tile_height - 1; i++) {
            for (int j = 1; j < tile_width - 1; j++) {

                index = (i + offset_height) * img_width + j + offset_width;
                data x = stream.read();
                mem[index] = x.get_data();

            }
        }
    }

    if (tile_index_width == 0 && tile_index_height > 0 && tile_index_height <= tile_num_height - 2) {
        for (int i = 1; i < tile_height - 1; i++) {
            for (int j = 0; j < tile_width - 1; j++) {

                index = (i + offset_height) * img_width + j + offset_width;
                data x = stream.read();
                mem[index] = x.get_data();

            }
        }
    }

    if (tile_index_width > 0 && tile_index_height > 0 && tile_index_width <= tile_num_width - 2 && tile_index_height <= tile_num_height - 2) {
        for (int i = 1; i < tile_height - 1; i++) {
            for (int j = 1; j < tile_width - 1; j++) {
                
                index = (i + offset_height) * img_width + j + offset_width;
                data x = stream.read();
                mem[index] = x.get_data();

            }
        }
    }

    if (tile_index_height == 0 && tile_index_width == tile_num_width - 1) {
        for (int i = 0; i < tile_height - 1; i++) {
            for (int j = 1; j < tile_width; j++) {
                if (j + offset_width < img_width) {
                    
                    index = (i + offset_height) * img_width + j + offset_width;
                    data x = stream.read();
                    mem[index] = x.get_data();
                
                }    
            }
        }
    }

    if (tile_index_height > 0 && tile_index_height <= tile_num_height - 2 && tile_index_width == tile_num_width - 1) {
        for (int i = 1; i < tile_height - 1; i++) {
            for (int j = 1; j < tile_width; j++) {
                if (j + offset_width < img_width) {

                    index = (i + offset_height) * img_width + j + offset_width;
                    data x = stream.read();
                    mem[index] = x.get_data();

                }
            }
        }
    }

    if (tile_index_width == 0 && tile_index_height == tile_num_height - 1) {
        for (int i = 1; i < tile_height; i++) {
            for (int j = 0; j < tile_width - 1; j++) {
                if (i + offset_height < img_height) {

                    index = (i + offset_height) * img_width + j + offset_width;
                    data x = stream.read();
                    mem[index] = x.get_data();

                }
            }
        }
    }

    if (tile_index_height == tile_num_height - 1 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
        for (int i = 1; i < tile_height; i++) {
            for (int j = 1; j < tile_width - 1; j++) {
                if (i + offset_height < img_height) {

                    index = (i + offset_height) * img_width + j + offset_width;
                    data x = stream.read();
                    mem[index] = x.get_data();

                }
            }
        }
    }

    if (tile_index_height == tile_num_height - 1 && tile_index_width == tile_num_width - 1) {
        for (int i = 1; i < tile_height; i++) {
            for (int j = 1; j < tile_width; j++) {
                if ((i + offset_height < img_height) && (j + offset_width < img_width)) {

                    index = (i + offset_height) * img_width + j + offset_width;
                    data x = stream.read();
                    mem[index] = x.get_data();

                }
            }
        }
    }

}
