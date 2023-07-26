#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>


// // host 端代码参考

// // 一张图片的 tile 个数
// unsigned tile_num_width  = ceil((float)(img_width - tile_width) / (tile_width - 2)) + 1;
// unsigned tile_num_height = ceil((float)(img_height - tile_height) / (tile_height - 2)) + 1;

// // 计算所有图片的总元素个数 && 一张图片的元素个数
// // 这里的 size_bytes 是所有图片的总大小
// unsigned element_size = data_width / CHAR_BIT;
// unsigned img_size     = img_width * img_height;
// unsigned elements     = size_bytes / element_size;

// // 遍历所有的图片
// for (unsigned offset = 0; offset < elements; offset += matrix_size) {

//     // 遍历一张图片的所有的 tile
//     for (int i = 0; i < tile_num_height; i++) {
//         for (int j = 0; j < tile_num_width; j++) {

//             // 当前 tile 的偏移
//             unsigned width_offset  = j * (tile_width - 2);
//             unsigned height_offset = i * (tile_height - 2);

//             // 假设 AIE kernel 的个数为 kernel_num
//             // 这里要：
//             // 声明 kernel_num 个 xrt::kerel
//             // 声明 kernel_num 个 tile 大小的输入缓冲 （xrt::bo）
//             // 声明 kernel_num 个 tile 大小的输出缓冲
//             // 声明 kernel_num 个 PL 核
//             // 

//             // 当前 tile 属于第几个 kernel 的第几个 tile 用取余和除法操作获得即可
//         }
//     }

// }




// 对一张图片的指定位置进行 tile 操作
template <unsigned img_width, unsigned img_height, unsigned tile_width, unsigned tile_height, unsigned width_offset, unsigned height_offset, unsigned data_width>
void tile(ap_int<data_width> *mem, hls::stream<qdma_axis<data_width, 0, 0, 0>> &stream) {

    using data = qdma_axis<data_width, 0, 0, 0>;

    // 遍历当前的 tile
    for (unsigned ti = 0; ti < tile_height; ti++) {
        for (unsigned tj = 0; tj < tile_width; tj++) {

            int index = 0;
            
            // 判断是否遍历到图片边缘
            bool edge_flag_width  = ((tj + width_offset) == (img_width));
            bool edge_flag_height = ((ti + height_offset) == (img_height));

            // 遍历到图片边缘后需要进行 padding 操作 
            // index == -1 表示补零
            if (!edge_flag_height && !edge_flag_width)
                index = (ti + height_offset) * img_width + tj + width_offset;                        
            else if (edge_flag_height && !edge_flag_width)
                index = (img_height - 1) * img_width + tj + width_offset;
            else if (!edge_flag_height && edge_flag_width)
                index = (ti + height_offset) * img_width + img_width - 1;
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
