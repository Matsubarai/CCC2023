#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>
#include "config.h"

void sticker_mmtransfer(ap_int<DWIDTH> *mem_in1, ap_int<DWIDTH> *mem_in2, ap_int<DWIDTH> *mem_in3, 
ap_int<DWIDTH> *mem_in4, ap_int<DWIDTH> *mem_in5, ap_int<DWIDTH> *mem_in6, ap_int<DWIDTH> *mem_in7,
ap_int<DWIDTH> *mem_out,
unsigned count[AIE_KERNEL_NUMBER], unsigned aie_index, unsigned mem_out_index);


// 将当前横纵坐标对应的 tile 拼接到图片中
void sticker_mm2mm(ap_int<DWIDTH> *mem_in1, ap_int<DWIDTH> *mem_in2, ap_int<DWIDTH> *mem_in3, 
ap_int<DWIDTH> *mem_in4, ap_int<DWIDTH> *mem_in5, ap_int<DWIDTH> *mem_in6, ap_int<DWIDTH> *mem_in7,
ap_int<DWIDTH> *mem_out) {

    // 每张图片的 tile 个数（width 和 height 两个维度）
    unsigned tile_num_width  = ceil((float)(img_width  - tile_width)  / (tile_width  - 2)) + 1;
    unsigned tile_num_height = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

    // 用作 mem_out 的索引
    unsigned mem_out_index;
    // 用作每个 mem_in 的索引
    unsigned count[AIE_KERNEL_NUMBER] = {0};

    // 遍历所有图片
    for (unsigned img_index = 0; img_index< img_number; img_index++) {

        // 已经处理过的图片对应的元素个数
        unsigned offset_img = img_index * img_width * img_height;

        // 一张图片 一个 aie kernel 需要计算的 tile 个数
        unsigned tile_per_img = ceil((float)(tile_num_width * tile_num_height) / AIE_KERNEL_NUMBER); 
        
        // 遍历所有的 tile
        for (unsigned tile_index_height = 0; tile_index_height < tile_num_height; tile_index_height++) {
            for (unsigned tile_index_width = 0; tile_index_width < tile_num_width; tile_index_width++) {

                // 当前的 tile 应该从第 aie_index 个 aie kernel 对应的 mem 处取得
                unsigned aie_index = (tile_index_height * tile_num_width + tile_index_width) % AIE_KERNEL_NUMBER;

                // 当前 tile 在当前图片中的偏移
                unsigned offset_width  = tile_index_width  * (tile_width  - 2);
                unsigned offset_height = tile_index_height * (tile_height - 2);

                if (tile_index_height == 0 && tile_index_width == 0) {
                    for (int th = 0; th < tile_height - 1; th++) {
                        for (int tw = 0; tw < tile_width - 1; tw++) {

                            mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                            sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                            count, aie_index, mem_out_index);
                        }
                    }
                }

                if (tile_index_height == 0 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
                    for (int th = 0; th < tile_height - 1; th++) {
                        for (int tw = 1; tw < tile_width - 1; tw++) {

                            mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                            sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                            count, aie_index, mem_out_index);

                        }
                    }
                }

                if (tile_index_width == 0 && tile_index_height > 0 && tile_index_height <= tile_num_height - 2) {
                    for (int th = 1; th < tile_height - 1; th++) {
                        for (int tw = 0; tw < tile_width - 1; tw++) {

                            mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                            sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                            count, aie_index, mem_out_index);

                        }
                    }
                }

                if (tile_index_width > 0 && tile_index_height > 0 && tile_index_width <= tile_num_width - 2 && tile_index_height <= tile_num_height - 2) {
                    for (int th = 1; th < tile_height - 1; th++) {
                        for (int tw = 1; tw < tile_width - 1; tw++) {
                            
                            mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                            sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                            count, aie_index, mem_out_index);

                        }
                    }
                }

                if (tile_index_height == 0 && tile_index_width == tile_num_width - 1) {
                    for (int th = 0; th < tile_height - 1; th++) {
                        for (int tw = 1; tw < tile_width; tw++) {
                            if (tw + offset_width < img_width) {
                                
                                mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                                sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                                count, aie_index, mem_out_index);
                            
                            }    
                        }
                    }
                }

                if (tile_index_height > 0 && tile_index_height <= tile_num_height - 2 && tile_index_width == tile_num_width - 1) {
                    for (int th = 1; th < tile_height - 1; th++) {
                        for (int tw = 1; tw < tile_width; tw++) {
                            if (tw + offset_width < img_width) {

                                mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                                sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

                if (tile_index_width == 0 && tile_index_height == tile_num_height - 1) {
                    for (int th = 1; th < tile_height; th++) {
                        for (int tw = 0; tw < tile_width - 1; tw++) {
                            if (th + offset_height < img_height) {

                                mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                                sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

                if (tile_index_height == tile_num_height - 1 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
                    for (int th = 1; th < tile_height; th++) {
                        for (int tw = 1; tw < tile_width - 1; tw++) {
                            if (th + offset_height < img_height) {

                                mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                                sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

                if (tile_index_height == tile_num_height - 1 && tile_index_width == tile_num_width - 1) {
                    for (int th = 1; th < tile_height; th++) {
                        for (int tw = 1; tw < tile_width; tw++) {
                            if ((th + offset_height < img_height) && (tw + offset_width < img_width)) {

                                mem_out_index = (th + offset_height) * img_width + tw + offset_width + offset_img;
                                sticker_mmtransfer(mem_in1, mem_in2, mem_in3, mem_in4, mem_in5, mem_in6, mem_in7, mem_out,
                                                                count, aie_index, mem_out_index);

                            }
                        }
                    }
                }

            }
        }
    }
}


void sticker_mmtransfer(ap_int<DWIDTH> *mem_in1, ap_int<DWIDTH> *mem_in2, ap_int<DWIDTH> *mem_in3, 
ap_int<DWIDTH> *mem_in4, ap_int<DWIDTH> *mem_in5, ap_int<DWIDTH> *mem_in6, ap_int<DWIDTH> *mem_in7,
ap_int<DWIDTH> *mem_out,
unsigned count[AIE_KERNEL_NUMBER], unsigned aie_index, unsigned mem_out_index) {

    switch(aie_index) {
        case 0:
            mem_out[mem_out_index] = mem_in1[count[aie_index]++];
            break;
        case 1:
            mem_out[mem_out_index] = mem_in2[count[aie_index]++];
            break;
        case 2:
            mem_out[mem_out_index] = mem_in3[count[aie_index]++];
            break;
        case 3:
            mem_out[mem_out_index] = mem_in4[count[aie_index]++];
            break;
        case 4:
            mem_out[mem_out_index] = mem_in5[count[aie_index]++];
            break;
        case 5:
            mem_out[mem_out_index] = mem_in6[count[aie_index]++];
            break;
        case 6:
            mem_out[mem_out_index] = mem_in7[count[aie_index]++];
            break;
        default:
            mem_out[mem_out_index] = mem_in1[count[aie_index]++];
    }
}
