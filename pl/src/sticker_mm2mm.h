#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>

template <unsigned data_width>
void sticker_mmtransfer(ap_int<data_width> *mem_in1, ap_int<data_width> *mem_in2, ap_int<data_width> *mem_in3, ap_int<data_width> *mem_in4, ap_int<data_width> *mem_in5,
ap_int<data_width> *mem_in6, ap_int<data_width> *mem_in7, ap_int<data_width> *mem_in8, ap_int<data_width> *mem_in9, ap_int<data_width> *mem_in10, 
ap_int<data_width> *mem_in11, ap_int<data_width> *mem_in12, ap_int<data_width> *mem_in13, ap_int<data_width> *mem_in14, ap_int<data_width> *mem_in15,
ap_int<data_width> *mem_out,
unsigned count[15], unsigned aie_index, unsigned mem_out_index);



// 将当前横纵坐标对应的 tile 拼接到图片中
template <unsigned img_width, unsigned img_height, unsigned img_number, unsigned tile_width, unsigned tile_height, unsigned aie_kernel_num, unsigned data_width>
void sticker(ap_int<data_width> *mem_in1, ap_int<data_width> *mem_in2, ap_int<data_width> *mem_in3, ap_int<data_width> *mem_in4, ap_int<data_width> *mem_in5,
ap_int<data_width> *mem_in6, ap_int<data_width> *mem_in7, ap_int<data_width> *mem_in8, ap_int<data_width> *mem_in9, ap_int<data_width> *mem_in10, 
ap_int<data_width> *mem_in11, ap_int<data_width> *mem_in12, ap_int<data_width> *mem_in13, ap_int<data_width> *mem_in14, ap_int<data_width> *mem_in15,
ap_int<data_width> *mem_out) {

    // 计算一张图片有多少 tile
    unsigned tile_num_width  = ceil((float)(img_width - tile_width) / (tile_width - 2)) + 1;
    unsigned tile_num_height = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

    unsigned mem_out_index;
    unsigned count[15] = {0};
    // unsigned mem_in_index;

    // 遍历所有图片
    for (unsigned img_index = 0; img_index< img_number; img_index++) {

        unsigned offset_img = img_index * img_width * img_height;
        // 一张图片 一个 aie kernel 需要计算的 tile 个数
        unsigned tile_per_img = ceil((float)(tile_num_width * tile_num_height) / aie_kernel_num); 
        
        // 遍历所有的 tile
        for (unsigned tile_index_height = 0; tile_index_height < tile_num_height; tile_index_height++) {
            for (unsigned tile_index_width = 0; tile_index_width < tile_num_width; tile_index_width++) {

                // 当前的 tile 应该从第 aie_index 个 aie kernel 对应的 mem 处取得
                unsigned aie_index = (tile_index_height * tile_num_width + tile_index_width) % aie_kernel_num;
                // // mem 的起始偏移为 offset_aie
                // unsigned offset_aie = (img_index * tile_per_img + (tile_index_height * tile_num_width + tile_index_width) / aie_kernel_num) * tile_width * tile_height;

                // 当前 tile 在当前图片中的偏移
                unsigned offset_width  = tile_index_width * (tile_width - 2);
                unsigned offset_height = tile_index_height * (tile_height - 2);

                if (tile_index_height == 0 && tile_index_width == 0) {
                    for (int i = 0; i < tile_height - 1; i++) {
                        for (int j = 0; j < tile_width - 1; j++) {

                            mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                            sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                            mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                            count, aie_index, mem_out_index);
                        }
                    }
                }

                if (tile_index_height == 0 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
                    for (int i = 0; i < tile_height - 1; i++) {
                        for (int j = 1; j < tile_width - 1; j++) {

                            mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                            sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                            mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                            count, aie_index, mem_out_index);

                        }
                    }
                }

                if (tile_index_width == 0 && tile_index_height > 0 && tile_index_height <= tile_num_height - 2) {
                    for (int i = 1; i < tile_height - 1; i++) {
                        for (int j = 0; j < tile_width - 1; j++) {

                            mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                            sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                            mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                            count, aie_index, mem_out_index);

                        }
                    }
                }

                if (tile_index_width > 0 && tile_index_height > 0 && tile_index_width <= tile_num_width - 2 && tile_index_height <= tile_num_height - 2) {
                    for (int i = 1; i < tile_height - 1; i++) {
                        for (int j = 1; j < tile_width - 1; j++) {
                            
                            mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                            sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                            mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                            count, aie_index, mem_out_index);

                        }
                    }
                }

                if (tile_index_height == 0 && tile_index_width == tile_num_width - 1) {
                    for (int i = 0; i < tile_height - 1; i++) {
                        for (int j = 1; j < tile_width; j++) {
                            if (j + offset_width < img_width) {
                                
                                mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                                sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                                mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                                count, aie_index, mem_out_index);
                            
                            }    
                        }
                    }
                }

                if (tile_index_height > 0 && tile_index_height <= tile_num_height - 2 && tile_index_width == tile_num_width - 1) {
                    for (int i = 1; i < tile_height - 1; i++) {
                        for (int j = 1; j < tile_width; j++) {
                            if (j + offset_width < img_width) {

                                mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                                sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                                mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

                if (tile_index_width == 0 && tile_index_height == tile_num_height - 1) {
                    for (int i = 1; i < tile_height; i++) {
                        for (int j = 0; j < tile_width - 1; j++) {
                            if (i + offset_height < img_height) {

                                mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                                sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                                mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

                if (tile_index_height == tile_num_height - 1 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
                    for (int i = 1; i < tile_height; i++) {
                        for (int j = 1; j < tile_width - 1; j++) {
                            if (i + offset_height < img_height) {

                                mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                                sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                                mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

                if (tile_index_height == tile_num_height - 1 && tile_index_width == tile_num_width - 1) {
                    for (int i = 1; i < tile_height; i++) {
                        for (int j = 1; j < tile_width; j++) {
                            if ((i + offset_height < img_height) && (j + offset_width < img_width)) {

                                mem_out_index = (i + offset_height) * img_width + j + offset_width + offset_img;
                                sticker_mmtransfer<data_width>(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_in8, mem_in9
                                                                mem_in10, mem_in11, mem_in12, mem_in13, mem_in14, mem_in15, mem_out
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

            }
        }
    }
}


template <unsigned data_width>
void sticker_mmtransfer(ap_int<data_width> *mem_in1, ap_int<data_width> *mem_in2, ap_int<data_width> *mem_in3, ap_int<data_width> *mem_in4, ap_int<data_width> *mem_in5,
ap_int<data_width> *mem_in6, ap_int<data_width> *mem_in7, ap_int<data_width> *mem_in8, ap_int<data_width> *mem_in9, ap_int<data_width> *mem_in10, 
ap_int<data_width> *mem_in11, ap_int<data_width> *mem_in12, ap_int<data_width> *mem_in13, ap_int<data_width> *mem_in14, ap_int<data_width> *mem_in15,
ap_int<data_width> *mem_out,
unsigned count[15], unsigned aie_index, unsigned mem_out_index) {

    switch(aie_index) {
        case 1:
            mem_out[mem_out_index] = mem_in1[count[aie_index]++];
            break;
        case 2:
            mem_out[mem_out_index] = mem_in2[count[aie_index]++];
            break;
        case 3:
            mem_out[mem_out_index] = mem_in3[count[aie_index]++];
            break;
        case 4:
            mem_out[mem_out_index] = mem_in4[count[aie_index]++];
            break;
        case 5:
            mem_out[mem_out_index] = mem_in5[count[aie_index]++];
            break;
        case 6:
            mem_out[mem_out_index] = mem_in6[count[aie_index]++];
            break;
        case 7:
            mem_out[mem_out_index] = mem_in7[count[aie_index]++];
            break;
        case 8:
            mem_out[mem_out_index] = mem_in8[count[aie_index]++];
            break;
        case 9:
            mem_out[mem_out_index] = mem_in9[count[aie_index]++];
            break;
        case 10:
            mem_out[mem_out_index] = mem_in10[count[aie_index]++];
            break;
        case 11:
            mem_out[mem_out_index] = mem_in11[count[aie_index]++];
            break;
        case 12:
            mem_out[mem_out_index] = mem_in12[count[aie_index]++];
            break;
        case 13:
            mem_out[mem_out_index] = mem_in13[count[aie_index]++];
            break;
        case 14:
            mem_out[mem_out_index] = mem_in14[count[aie_index]++];
            break;
        case 15:
            mem_out[mem_out_index] = mem_in15[count[aie_index]++];
            break;
        default:
            mem_out[mem_out_index] = mem_in1[count[aie_index]++];
    }
}
