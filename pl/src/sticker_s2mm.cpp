if (tile_index_height == 0 && tile_index_width == 0) {
                            if (th >= 0 && th < tile_height - 1 && tw >= 0 && tw < tile_width - 1) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_height == 0 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
                            if (th >= 0 && th < tile_height - 1 && tw >= 1 && tw < tile_width - 1) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_width == 0 && tile_index_height > 0 && tile_index_height <= tile_num_height - 2) {
                            if (th >= 1 && th < tile_height - 1 && tw >= 0 && tw < tile_width - 1) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_width > 0 && tile_index_height > 0 && tile_index_width <= tile_num_width - 2 && tile_index_height <= tile_num_height - 2) {
                            if (th >= 1 && th < tile_height - 1 && tw >= 1 && tw < tile_width - 1) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_height == 0 && tile_index_width == tile_num_width - 1) {
                            if (th >= 0 && th < tile_height - 1 && tw >= 1 && tw < tile_width && tw + offset_width < img_width) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_height > 0 && tile_index_height <= tile_num_height - 2 && tile_index_width == tile_num_width - 1) {
                            if (th >= 1 && th < tile_height - 1 && tw >= 1 && tw < tile_width && tw + offset_width < img_width) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_width == 0 && tile_index_height == tile_num_height - 1) {
                            if (th >= 1 && th < tile_height && tw >= 0 && tw < tile_width - 1 && th + offset_height < img_height) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_height == tile_num_height - 1 && tile_index_width > 0 && tile_index_width <= tile_num_width - 2) {
                            if (th >= 1 && th < tile_height && tw >= 1 && tw < tile_width - 1 && th + offset_height < img_height) {
                                mem_out[mem_out_index] = x;
                            }
                        }

                        else if (tile_index_height == tile_num_height - 1 && tile_index_width == tile_num_width - 1) {
                            if (th >= 1 && th < tile_height && tw >= 1 && tw < tile_width && (th + offset_height < img_height) && (tw + offset_width < img_width)) {
                                mem_out[mem_out_index] = x;
                            }
                        }
