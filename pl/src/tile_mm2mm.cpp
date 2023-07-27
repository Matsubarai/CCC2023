#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>
#include "config.h"

// 对一张图片的指定位置进行 tile 操作
void tile_mm2mm(ap_int<DWIDTH> *mem_in, 
ap_int<DWIDTH> *mem_out1, ap_int<DWIDTH> *mem_out2, ap_int<DWIDTH> *mem_out3, ap_int<DWIDTH> *mem_out4, 
ap_int<DWIDTH> *mem_out5, ap_int<DWIDTH> *mem_out6, ap_int<DWIDTH> *mem_out7) {


    // 每张图片的 tile 个数（width 和 height 两个维度）
    unsigned tile_width_number  = ceil((float)(img_width  - tile_width)  / (tile_width  - 2)) + 1;
    unsigned tile_height_number = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

    // 用作每个 mem_out 的索引
    unsigned count[AIE_KERNEL_NUMBER] = {0};
    // 用作 mem_in 的索引
    int mem_in_index;

    // 遍历所有图片
    for (unsigned i = 0; i < img_number; i++) {

        // 已经处理过的图片对应的元素个数
        unsigned offset_img = i * img_width * img_height;

        // 遍历所有的 tile
        for (unsigned j = 0; j < tile_height_number; j++) {
            for (unsigned k = 0; k < tile_width_number; k++) {

                // 当前的 tile 应该传输给第 aie_index 个 aie kernel
                unsigned aie_index = (j * tile_width_number + k) % AIE_KERNEL_NUMBER;
                
                // 当前 tile 相对于第一个元素的偏移
                unsigned offset_width  = k * (tile_width - 2);
                unsigned offset_height = j * (tile_height - 2);

                // 遍历当前的 tile
                for (unsigned ti = 0; ti < tile_height; ti++) {
                    for (unsigned tj = 0; tj < tile_width; tj++) {
                        
                        // 判断是否遍历到图片边缘
                        bool edge_flag_width  = ((tj + offset_width) == (img_width));
                        bool edge_flag_height = ((ti + offset_height) == (img_height));

                        // 遍历到图片边缘后需要进行 padding 操作 
                        // mem_in_index == -1 表示补零
                        if (!edge_flag_height && !edge_flag_width)
                            mem_in_index = (ti + offset_height) * img_width + tj + offset_width + offset_img;                        
                        else if (edge_flag_height && !edge_flag_width)
                            mem_in_index = (img_height - 1) * img_width + tj + offset_width + offset_img;
                        else if (!edge_flag_height && edge_flag_width)
                            mem_in_index = (ti + offset_height) * img_width + img_width - 1 + offset_img;
                        else if (edge_flag_height && edge_flag_width)
                            mem_in_index = (img_height - 1) * img_width + img_width - 1 + offset_img;
                        else
                            mem_in_index = -1;

                        // 将分块好的数据存入对应 aie 所读取的 mem 区域
                        switch(aie_index) {
                            case 0:
                                if (mem_in_index == -1)
                                    mem_out1[count[aie_index]++] = 0;
                                else 
                                    mem_out1[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            case 1:
                                if (mem_in_index == -1)
                                    mem_out2[count[aie_index]++] = 0;
                                else 
                                    mem_out2[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            case 2:
                                if (mem_in_index == -1)
                                    mem_out3[count[aie_index]++] = 0;
                                else 
                                    mem_out3[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            case 3:
                                if (mem_in_index == -1)
                                    mem_out4[count[aie_index]++] = 0;
                                else 
                                    mem_out4[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            case 4:
                                if (mem_in_index == -1)
                                    mem_out5[count[aie_index]++] = 0;
                                else 
                                    mem_out5[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            case 5:
                                if (mem_in_index == -1)
                                    mem_out6[count[aie_index]++] = 0;
                                else 
                                    mem_out6[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            case 6:
                                if (mem_in_index == -1)
                                    mem_out7[count[aie_index]++] = 0;
                                else 
                                    mem_out7[count[aie_index]++] = mem_in[mem_in_index];
                                break;
                            default:
                                if (mem_in_index == -1)
                                    mem_out1[count[aie_index]++] = 0;
                                else 
                                    mem_out1[count[aie_index]++] = mem_in[mem_in_index];
                        }
                    }
                }
            }
        }
    }
}
