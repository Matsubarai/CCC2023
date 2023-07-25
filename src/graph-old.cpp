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
#include <iostream>
#include <fstream>
#include <cstring>
#include "graph.h"

PLIO* in1 = new PLIO("DataIn1", adf::plio_32_bits, "data/input1.txt");
PLIO* out1 = new PLIO("DataOut1", adf::plio_32_bits, "data/output1.txt");

PLIO* in2 = new PLIO("DataIn2", adf::plio_32_bits, "data/input2.txt");
PLIO* out2 = new PLIO("DataOut2", adf::plio_32_bits, "data/output2.txt");

PLIO* in3 = new PLIO("DataIn3", adf::plio_32_bits, "data/input3.txt");
PLIO* out3 = new PLIO("DataOut3", adf::plio_32_bits, "data/output3.txt");

PLIO* in4 = new PLIO("DataIn4", adf::plio_32_bits, "data/input4.txt");
PLIO* out4 = new PLIO("DataOut4", adf::plio_32_bits, "data/output4.txt");

PLIO* in5 = new PLIO("DataIn5", adf::plio_32_bits, "data/input5.txt");
PLIO* out5 = new PLIO("DataOut5", adf::plio_32_bits, "data/output5.txt");

PLIO* in6 = new PLIO("DataIn6", adf::plio_32_bits, "data/input6.txt");
PLIO* out6 = new PLIO("DataOut6", adf::plio_32_bits, "data/output6.txt");

PLIO* in7 = new PLIO("DataIn7", adf::plio_32_bits, "data/input7.txt");
PLIO* out7 = new PLIO("DataOut7", adf::plio_32_bits, "data/output7.txt");

PLIO* in8 = new PLIO("DataIn8", adf::plio_32_bits, "data/input8.txt");
PLIO* out8 = new PLIO("DataOut8", adf::plio_32_bits, "data/output8.txt");

PLIO* in9 = new PLIO("DataIn9", adf::plio_32_bits, "data/input9.txt");
PLIO* out9 = new PLIO("DataOut9", adf::plio_32_bits, "data/output9.txt");

PLIO* in10 = new PLIO("DataIn10", adf::plio_32_bits, "data/input10.txt");
PLIO* out10 = new PLIO("DataOut10", adf::plio_32_bits, "data/output10.txt");

PLIO* in11 = new PLIO("DataIn11", adf::plio_32_bits, "data/input11.txt");
PLIO* out11 = new PLIO("DataOut11", adf::plio_32_bits, "data/output11.txt");

PLIO* in12 = new PLIO("DataIn12", adf::plio_32_bits, "data/input12.txt");
PLIO* out12 = new PLIO("DataOut12", adf::plio_32_bits, "data/output12.txt");

PLIO* in13 = new PLIO("DataIn13", adf::plio_32_bits, "data/input13.txt");
PLIO* out13 = new PLIO("DataOut13", adf::plio_32_bits, "data/output13.txt");

PLIO* in14 = new PLIO("DataIn14", adf::plio_32_bits, "data/input14.txt");
PLIO* out14 = new PLIO("DataOut14", adf::plio_32_bits, "data/output14.txt");

PLIO* in15 = new PLIO("DataIn15", adf::plio_32_bits, "data/input15.txt");
PLIO* out15 = new PLIO("DataOut15", adf::plio_32_bits, "data/output15.txt");

PLIO* in16 = new PLIO("DataIn16", adf::plio_32_bits, "data/input16.txt");
PLIO* out16 = new PLIO("DataOut16", adf::plio_32_bits, "data/output16.txt");

PLIO* in17 = new PLIO("DataIn17", adf::plio_32_bits, "data/input17.txt");
PLIO* out17 = new PLIO("DataOut17", adf::plio_32_bits, "data/output17.txt");

PLIO* in18 = new PLIO("DataIn18", adf::plio_32_bits, "data/input18.txt");
PLIO* out18 = new PLIO("DataOut18", adf::plio_32_bits, "data/output18.txt");

PLIO* in19 = new PLIO("DataIn19", adf::plio_32_bits, "data/input19.txt");
PLIO* out19 = new PLIO("DataOut19", adf::plio_32_bits, "data/output19.txt");

PLIO* in20 = new PLIO("DataIn20", adf::plio_32_bits, "data/input20.txt");
PLIO* out20 = new PLIO("DataOut20", adf::plio_32_bits, "data/output20.txt");

PLIO* in21 = new PLIO("DataIn21", adf::plio_32_bits, "data/input21.txt");
PLIO* out21 = new PLIO("DataOut21", adf::plio_32_bits, "data/output21.txt");

PLIO* in22 = new PLIO("DataIn22", adf::plio_32_bits, "data/input22.txt");
PLIO* out22 = new PLIO("DataOut22", adf::plio_32_bits, "data/output22.txt");

PLIO* in23 = new PLIO("DataIn23", adf::plio_32_bits, "data/input23.txt");
PLIO* out23 = new PLIO("DataOut23", adf::plio_32_bits, "data/output23.txt");

PLIO* in24 = new PLIO("DataIn24", adf::plio_32_bits, "data/input24.txt");
PLIO* out24 = new PLIO("DataOut24", adf::plio_32_bits, "data/output24.txt");

PLIO* in25 = new PLIO("DataIn25", adf::plio_32_bits, "data/input25.txt");
PLIO* out25 = new PLIO("DataOut25", adf::plio_32_bits, "data/output25.txt");

PLIO* in26 = new PLIO("DataIn26", adf::plio_32_bits, "data/input26.txt");
PLIO* out26 = new PLIO("DataOut26", adf::plio_32_bits, "data/output26.txt");

PLIO* in27 = new PLIO("DataIn27", adf::plio_32_bits, "data/input27.txt");
PLIO* out27 = new PLIO("DataOut27", adf::plio_32_bits, "data/output27.txt");

PLIO* in28 = new PLIO("DataIn28", adf::plio_32_bits, "data/input28.txt");
PLIO* out28 = new PLIO("DataOut28", adf::plio_32_bits, "data/output28.txt");

PLIO* in29 = new PLIO("DataIn29", adf::plio_32_bits, "data/input29.txt");
PLIO* out29 = new PLIO("DataOut29", adf::plio_32_bits, "data/output29.txt");

PLIO* in30 = new PLIO("DataIn30", adf::plio_32_bits, "data/input30.txt");
PLIO* out30 = new PLIO("DataOut30", adf::plio_32_bits, "data/output30.txt");

PLIO* in31 = new PLIO("DataIn31", adf::plio_32_bits, "data/input31.txt");
PLIO* out31 = new PLIO("DataOut31", adf::plio_32_bits, "data/output31.txt");

PLIO* in32 = new PLIO("DataIn32", adf::plio_32_bits, "data/input32.txt");
PLIO* out32 = new PLIO("DataOut32", adf::plio_32_bits, "data/output32.txt");


simulation::platform<32, 32> platform(in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12,
									  in13, in14, in15, in16, in17, in18, in19, in20, in21, in22, in23, in24,
									  in25, in26, in27, in28, in29, in30, in31, in32,
									  out1, out2, out3, out4, out5, out6, out7, out8, out9, out10, out11, out12,
									  out13, out14, out15, out16, out17, out18, out19, out20, out21, out22, out23, out24,
									  out25, out26, out27, out28, out29, out30, out31, out32);

two_node_pipeline filter_graph;

connect<> net0(platform.src[0], filter_graph.in1);
connect<> net1(filter_graph.out1, platform.sink[0]);
connect<> net2(platform.src[1], filter_graph.in2);
connect<> net3(filter_graph.out2, platform.sink[1]);
connect<> net4(platform.src[2], filter_graph.in3);
connect<> net5(filter_graph.out3, platform.sink[2]);
connect<> net6(platform.src[3], filter_graph.in4);
connect<> net7(filter_graph.out4, platform.sink[3]);
connect<> net8(platform.src[4], filter_graph.in5);
connect<> net9(filter_graph.out5, platform.sink[4]);
connect<> net10(platform.src[5], filter_graph.in6);
connect<> net11(filter_graph.out6, platform.sink[5]);
connect<> net12(platform.src[6], filter_graph.in7);
connect<> net13(filter_graph.out7, platform.sink[6]);
connect<> net14(platform.src[7], filter_graph.in8);
connect<> net15(filter_graph.out8, platform.sink[7]);
connect<> net16(platform.src[8], filter_graph.in9);
connect<> net17(filter_graph.out9, platform.sink[8]);
connect<> net18(platform.src[9], filter_graph.in10);
connect<> net19(filter_graph.out10, platform.sink[9]);
connect<> net20(platform.src[10], filter_graph.in11);
connect<> net21(filter_graph.out11, platform.sink[10]);
connect<> net22(platform.src[11], filter_graph.in12);
connect<> net23(filter_graph.out12, platform.sink[11]);
connect<> net24(platform.src[12], filter_graph.in13);
connect<> net25(filter_graph.out13, platform.sink[12]);
connect<> net26(platform.src[13], filter_graph.in14);
connect<> net27(filter_graph.out14, platform.sink[13]);
connect<> net28(platform.src[14], filter_graph.in15);
connect<> net29(filter_graph.out15, platform.sink[14]);
connect<> net30(platform.src[15], filter_graph.in16);
connect<> net31(filter_graph.out16, platform.sink[15]);
connect<> net32(platform.src[16], filter_graph.in17);
connect<> net33(filter_graph.out17, platform.sink[16]);
connect<> net34(platform.src[17], filter_graph.in18);
connect<> net35(filter_graph.out18, platform.sink[17]);
connect<> net36(platform.src[18], filter_graph.in19);
connect<> net37(filter_graph.out19, platform.sink[18]);
connect<> net38(platform.src[19], filter_graph.in20);
connect<> net39(filter_graph.out20, platform.sink[19]);
connect<> net40(platform.src[20], filter_graph.in21);
connect<> net41(filter_graph.out21, platform.sink[20]);
connect<> net42(platform.src[21], filter_graph.in22);
connect<> net43(filter_graph.out22, platform.sink[21]);
connect<> net44(platform.src[22], filter_graph.in23);
connect<> net45(filter_graph.out23, platform.sink[22]);
connect<> net46(platform.src[23], filter_graph.in24);
connect<> net47(filter_graph.out24, platform.sink[23]);
connect<> net48(platform.src[24], filter_graph.in25);
connect<> net49(filter_graph.out25, platform.sink[24]);
connect<> net50(platform.src[25], filter_graph.in26);
connect<> net51(filter_graph.out26, platform.sink[25]);
connect<> net52(platform.src[26], filter_graph.in27);
connect<> net53(filter_graph.out27, platform.sink[26]);
connect<> net54(platform.src[27], filter_graph.in28);
connect<> net55(filter_graph.out28, platform.sink[27]);
connect<> net56(platform.src[28], filter_graph.in29);
connect<> net57(filter_graph.out29, platform.sink[28]);
connect<> net58(platform.src[29], filter_graph.in30);
connect<> net59(filter_graph.out30, platform.sink[29]);
connect<> net60(platform.src[30], filter_graph.in31);
connect<> net61(filter_graph.out31, platform.sink[30]);
connect<> net62(platform.src[31], filter_graph.in32);
connect<> net63(filter_graph.out32, platform.sink[31]);



#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char** argv) {

    filter_graph.init();
    filter_graph.run(70);
    filter_graph.end();
    return 0;
}

#endif
