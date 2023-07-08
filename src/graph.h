/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <adf.h>
#include "kernels.h"
//#include "gauss2_stitcher.h"
//#include "gauss2_tiler.h"

using namespace adf;

class two_node_pipeline : public graph {
   private:
    // kernel tiler;
    // kernel stitcher;
    kernel gauss1;
    kernel gauss2;
    kernel gauss3;
    kernel gauss4;
    kernel gauss5;
    kernel gauss6;
    kernel gauss7;
    kernel gauss8;
    kernel gauss9;
    kernel gauss10;
    kernel gauss11;
    kernel gauss12;
    kernel gauss13;
    kernel gauss14;
    kernel gauss15;
    kernel gauss16;
    kernel gauss17;
    kernel gauss18;
    kernel gauss19;
    kernel gauss20;
    kernel gauss21;
    kernel gauss22;
    kernel gauss23;
    kernel gauss24;
    kernel gauss25;
    kernel gauss26;
    kernel gauss27;
    kernel gauss28;
    kernel gauss29;
    kernel gauss30;
    kernel gauss31;
    kernel gauss32;


   public:
    port<input> in1;
    port<output> out1;
    port<input> in2;
    port<output> out2;
    port<input> in3;
    port<output> out3;
    port<input> in4;
    port<output> out4;
    port<input> in5;
    port<output> out5;
    port<input> in6;
    port<output> out6;
    port<input> in7;
    port<output> out7;
    port<input> in8;
    port<output> out8;
    port<input> in9;
    port<output> out9;
    port<input> in10;
    port<output> out10;
    port<input> in11;
    port<output> out11;
    port<input> in12;
    port<output> out12;
    port<input> in13;
    port<output> out13;
    port<input> in14;
    port<output> out14;
    port<input> in15;
    port<output> out15;
    port<input> in16;
    port<output> out16;
    port<input> in17;
    port<output> out17;
    port<input> in18;
    port<output> out18;
    port<input> in19;
    port<output> out19;
    port<input> in20;
    port<output> out20;
    port<input> in21;
    port<output> out21;
    port<input> in22;
    port<output> out22;
    port<input> in23;
    port<output> out23;
    port<input> in24;
    port<output> out24;
    port<input> in25;
    port<output> out25;
    port<input> in26;
    port<output> out26;
    port<input> in27;
    port<output> out27;
    port<input> in28;
    port<output> out28;
    port<input> in29;
    port<output> out29;
    port<input> in30;
    port<output> out30;
    port<input> in31;
    port<output> out31;
    port<input> in32;
    port<output> out32;


    two_node_pipeline() {
        // tiler    = kernel::create(gauss2_tiler);
        gauss1 = kernel::create(filter2D);
        gauss2 = kernel::create(filter2D);
        gauss3 = kernel::create(filter2D);
        gauss4 = kernel::create(filter2D);
        gauss5 = kernel::create(filter2D);
        gauss6 = kernel::create(filter2D);
        gauss7 = kernel::create(filter2D);
        gauss8 = kernel::create(filter2D);
        gauss9 = kernel::create(filter2D);
        gauss10 = kernel::create(filter2D);
        gauss11 = kernel::create(filter2D);
        gauss12 = kernel::create(filter2D);
        gauss13 = kernel::create(filter2D);
        gauss14 = kernel::create(filter2D);
        gauss15 = kernel::create(filter2D);
        gauss16 = kernel::create(filter2D);
        gauss17 = kernel::create(filter2D);
        gauss18 = kernel::create(filter2D);
        gauss19 = kernel::create(filter2D);
        gauss20 = kernel::create(filter2D);
        gauss21 = kernel::create(filter2D);
        gauss22 = kernel::create(filter2D);
        gauss23 = kernel::create(filter2D);
        gauss24 = kernel::create(filter2D);
        gauss25 = kernel::create(filter2D);
        gauss26 = kernel::create(filter2D);
        gauss27 = kernel::create(filter2D);
        gauss28 = kernel::create(filter2D);
        gauss29 = kernel::create(filter2D);
        gauss30 = kernel::create(filter2D);
        gauss31 = kernel::create(filter2D);
        gauss32 = kernel::create(filter2D);


        // stitcher = kernel::create(gauss2_stitcher);

        // fabric<fpga>(tiler);
        // fabric<fpga>(stitcher);

        // connect< stream >(in,tiler.in[0]);

        // gauss1 processes 4096 32b blocks or 8192 byte blocks
        connect<adf::window<8192> >(in1, gauss1.in[0]);
        connect<adf::window<8192> >(in2, gauss2.in[0]);
        connect<adf::window<8192> >(in3, gauss3.in[0]);
        connect<adf::window<8192> >(in4, gauss4.in[0]);
        connect<adf::window<8192> >(in5, gauss5.in[0]);
        connect<adf::window<8192> >(in6, gauss6.in[0]);
        connect<adf::window<8192> >(in7, gauss7.in[0]);
        connect<adf::window<8192> >(in8, gauss8.in[0]);
        connect<adf::window<8192> >(in9, gauss9.in[0]);
        connect<adf::window<8192> >(in10, gauss10.in[0]);
        connect<adf::window<8192> >(in11, gauss11.in[0]);
        connect<adf::window<8192> >(in12, gauss12.in[0]);
        connect<adf::window<8192> >(in13, gauss13.in[0]);
        connect<adf::window<8192> >(in14, gauss14.in[0]);
        connect<adf::window<8192> >(in15, gauss15.in[0]);
        connect<adf::window<8192> >(in16, gauss16.in[0]);
        connect<adf::window<8192> >(in17, gauss17.in[0]);
        connect<adf::window<8192> >(in18, gauss18.in[0]);
        connect<adf::window<8192> >(in19, gauss19.in[0]);
        connect<adf::window<8192> >(in20, gauss20.in[0]);
        connect<adf::window<8192> >(in21, gauss21.in[0]);
        connect<adf::window<8192> >(in22, gauss22.in[0]);
        connect<adf::window<8192> >(in23, gauss23.in[0]);
        connect<adf::window<8192> >(in24, gauss24.in[0]);
        connect<adf::window<8192> >(in25, gauss25.in[0]);
        connect<adf::window<8192> >(in26, gauss26.in[0]);
        connect<adf::window<8192> >(in27, gauss27.in[0]);
        connect<adf::window<8192> >(in28, gauss28.in[0]);
        connect<adf::window<8192> >(in29, gauss29.in[0]);
        connect<adf::window<8192> >(in30, gauss30.in[0]);
        connect<adf::window<8192> >(in31, gauss31.in[0]);
        connect<adf::window<8192> >(in32, gauss32.in[0]);

        // connect< stream, window<8192> >(tiler.out[0], gauss1.in[0]);

        // gauss1 window passsed directly to gauss2
        connect<window<8192> >(gauss1.out[0], out1);
        connect<window<8192> >(gauss2.out[0], out2);
        connect<window<8192> >(gauss3.out[0], out3);
        connect<window<8192> >(gauss4.out[0], out4);
        connect<window<8192> >(gauss5.out[0], out5);
        connect<window<8192> >(gauss6.out[0], out6);
        connect<window<8192> >(gauss7.out[0], out7);
        connect<window<8192> >(gauss8.out[0], out8);
        connect<window<8192> >(gauss9.out[0], out9);
        connect<window<8192> >(gauss10.out[0], out10);
        connect<window<8192> >(gauss11.out[0], out11);
        connect<window<8192> >(gauss12.out[0], out12);
        connect<window<8192> >(gauss13.out[0], out13);
        connect<window<8192> >(gauss14.out[0], out14);
        connect<window<8192> >(gauss15.out[0], out15);
        connect<window<8192> >(gauss16.out[0], out16);
        connect<window<8192> >(gauss17.out[0], out17);
        connect<window<8192> >(gauss18.out[0], out18);
        connect<window<8192> >(gauss19.out[0], out19);
        connect<window<8192> >(gauss20.out[0], out20);
        connect<window<8192> >(gauss21.out[0], out21);
        connect<window<8192> >(gauss22.out[0], out22);
        connect<window<8192> >(gauss23.out[0], out23);
        connect<window<8192> >(gauss24.out[0], out24);
        connect<window<8192> >(gauss25.out[0], out25);
        connect<window<8192> >(gauss26.out[0], out26);
        connect<window<8192> >(gauss27.out[0], out27);
        connect<window<8192> >(gauss28.out[0], out28);
        connect<window<8192> >(gauss29.out[0], out29);
        connect<window<8192> >(gauss30.out[0], out30);
        connect<window<8192> >(gauss31.out[0], out31);
        connect<window<8192> >(gauss32.out[0], out32);


        // gauss2 window passed to output
//        connect<window<8192>, stream>(gauss2.out[0], out);
        // connect< window<8192>, stream >(gauss2.out[0], stitcher.in[0]);

        // connect< stream >(stitcher.out[0],out);

        // Pull the source from previous lab
        // source(tiler)    = "kernels/gauss2_tiler.cpp";
        source(gauss1) = "xf_filter2d.cc";
        source(gauss2) = "xf_filter2d.cc";
        source(gauss3) = "xf_filter2d.cc";
        source(gauss4) = "xf_filter2d.cc";
        source(gauss5) = "xf_filter2d.cc";
        source(gauss6) = "xf_filter2d.cc";
        source(gauss7) = "xf_filter2d.cc";
        source(gauss8) = "xf_filter2d.cc";
        source(gauss9) = "xf_filter2d.cc";
        source(gauss10) = "xf_filter2d.cc";
        source(gauss11) = "xf_filter2d.cc";
        source(gauss12) = "xf_filter2d.cc";
        source(gauss13) = "xf_filter2d.cc";
        source(gauss14) = "xf_filter2d.cc";
        source(gauss15) = "xf_filter2d.cc";
        source(gauss16) = "xf_filter2d.cc";
        source(gauss17) = "xf_filter2d.cc";
        source(gauss18) = "xf_filter2d.cc";
        source(gauss19) = "xf_filter2d.cc";
        source(gauss20) = "xf_filter2d.cc";
        source(gauss21) = "xf_filter2d.cc";
        source(gauss22) = "xf_filter2d.cc";
        source(gauss23) = "xf_filter2d.cc";
        source(gauss24) = "xf_filter2d.cc";
        source(gauss25) = "xf_filter2d.cc";
        source(gauss26) = "xf_filter2d.cc";
        source(gauss27) = "xf_filter2d.cc";
        source(gauss28) = "xf_filter2d.cc";
        source(gauss29) = "xf_filter2d.cc";
        source(gauss30) = "xf_filter2d.cc";
        source(gauss31) = "xf_filter2d.cc";
        source(gauss32) = "xf_filter2d.cc";

        // source(stitcher) = "kernels/gauss2_stitcher.cpp";

        // Initial mapping
        runtime<ratio>(gauss1) = 1;
        runtime<ratio>(gauss2) = 1;
        runtime<ratio>(gauss3) = 1;
        runtime<ratio>(gauss4) = 1;
        runtime<ratio>(gauss5) = 1;
        runtime<ratio>(gauss6) = 1;
        runtime<ratio>(gauss7) = 1;
        runtime<ratio>(gauss8) = 1;
        runtime<ratio>(gauss9) = 1;
        runtime<ratio>(gauss10) = 1;
        runtime<ratio>(gauss11) = 1;
        runtime<ratio>(gauss12) = 1;
        runtime<ratio>(gauss13) = 1;
        runtime<ratio>(gauss14) = 1;
        runtime<ratio>(gauss15) = 1;
        runtime<ratio>(gauss16) = 1;
        runtime<ratio>(gauss17) = 1;
        runtime<ratio>(gauss18) = 1;
        runtime<ratio>(gauss19) = 1;
        runtime<ratio>(gauss20) = 1;
        runtime<ratio>(gauss21) = 1;
        runtime<ratio>(gauss22) = 1;
        runtime<ratio>(gauss23) = 1;
        runtime<ratio>(gauss24) = 1;
        runtime<ratio>(gauss25) = 1;
        runtime<ratio>(gauss26) = 1;
        runtime<ratio>(gauss27) = 1;
        runtime<ratio>(gauss28) = 1;
        runtime<ratio>(gauss29) = 1;
        runtime<ratio>(gauss30) = 1;
        runtime<ratio>(gauss31) = 1;
        runtime<ratio>(gauss32) = 1;

    };
};

#endif
