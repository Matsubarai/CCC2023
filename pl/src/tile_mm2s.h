#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>



// 对一张图片的指定位置进行 tile 操作
template <unsigned img_width, unsigned img_height, unsigned tile_width, unsigned tile_height, unsigned data_width>
void tile(ap_int<data_width> *mem, hls::stream<qdma_axis<data_width, 0, 0, 0>> &stream, unsgined tile_index_width, unsigned tile_index_height) {

    using data = qdma_axis<data_width, 0, 0, 0>;

    // 当前 tile 的偏移
    unsigned offset_width  = tile_index_width * (tile_width - 2);
    unsigned offset_height = tile_index_height * (tile_height - 2);

    // 遍历当前的 tile
    for (unsigned ti = 0; ti < tile_height; ti++) {
        for (unsigned tj = 0; tj < tile_width; tj++) {

            int index = 0;
            
            // 判断是否遍历到图片边缘
            bool edge_flag_width  = ((tj + offset_width) == (img_width));
            bool edge_flag_height = ((ti + offset_height) == (img_height));

            // 遍历到图片边缘后需要进行 padding 操作 
            // index == -1 表示补零
            if (!edge_flag_height && !edge_flag_width)
                index = (ti + offset_height) * img_width + tj + offset_width;                        
            else if (edge_flag_height && !edge_flag_width)
                index = (img_height - 1) * img_width + tj + offset_width;
            else if (!edge_flag_height && edge_flag_width)
                index = (ti + offset_height) * img_width + img_width - 1;
            else if (edge_flag_height && edge_flag_width)
                index = (img_height - 1) * img_width + img_width - 1;
            else
                index = -1;

            // 从 mem 中取出对应数据 并将其放入 stream
            if (index == -1)
                data x { 0 };
            else
                data x { mem[index] };
            x.keep_all();
            stream.write(x);
        }
    }
}
