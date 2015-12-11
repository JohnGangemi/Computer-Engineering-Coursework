////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1995-2011 Xilinx, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//   ____  ____
//  /   /\/   /
// /___/  \  /    Vendor: Xilinx
// \   \   \/     Version: O.87xd
//  \   \         Application: netgen
//  /   /         Filename: adder_4b_ip.v
// /___/   /\     Timestamp: Thu Jan 15 02:43:51 2015
// \   \  /  \ 
//  \___\/\___\
//             
// Command	: -w -sim -ofmt verilog "E:/CSD LAB/lab01/ipcore_dir/tmp/_cg/adder_4b_ip.ngc" "E:/CSD LAB/lab01/ipcore_dir/tmp/_cg/adder_4b_ip.v" 
// Device	: 6slx45csg324-3
// Input file	: E:/CSD LAB/lab01/ipcore_dir/tmp/_cg/adder_4b_ip.ngc
// Output file	: E:/CSD LAB/lab01/ipcore_dir/tmp/_cg/adder_4b_ip.v
// # of Modules	: 1
// Design Name	: adder_4b_ip
// Xilinx        : C:\Xilinx\13.4\ISE_DS\ISE\
//             
// Purpose:    
//     This verilog netlist is a verification model and uses simulation 
//     primitives which may not represent the true implementation of the 
//     device, however the netlist is functionally correct and should not 
//     be modified. This file cannot be synthesized and should only be used 
//     with supported simulation tools.
//             
// Reference:  
//     Command Line Tools User Guide, Chapter 23 and Synthesis and Simulation Design Guide, Chapter 6
//             
////////////////////////////////////////////////////////////////////////////////

`timescale 1 ns/1 ps

module adder_4b_ip (
  clk, a, b, s
)/* synthesis syn_black_box syn_noprune=1 */;
  input clk;
  input [3 : 0] a;
  input [3 : 0] b;
  output [3 : 0] s;
  
  // synthesis translate_off
  
  wire N1;
  wire [4 : 1] \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output ;
  wire [3 : 0] \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple ;
  wire [3 : 0] \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum ;
  wire [2 : 0] \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple ;
  assign
    s[3] = \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [4],
    s[2] = \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [3],
    s[1] = \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [2],
    s[0] = \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [1];
  GND   XST_GND (
    .G(N1)
  );
  XORCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.carryxor0  (
    .CI(N1),
    .LI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [0]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [0])
  );
  XORCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.i_gt_1.carryxortop  (
    .CI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [2]),
    .LI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [3]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [3])
  );
  XORCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.i_gt_1.carrychaingen[2].carryxor  (
    .CI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [1]),
    .LI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [2]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [2])
  );
  XORCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.i_gt_1.carrychaingen[1].carryxor  (
    .CI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [0]),
    .LI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [1]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [1])
  );
  MUXCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.i_gt_1.carrychaingen[2].carrymux  (
    .CI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [1]),
    .DI(a[2]),
    .S(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [2]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [2])
  );
  MUXCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.i_gt_1.carrychaingen[1].carrymux  (
    .CI(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [0]),
    .DI(a[1]),
    .S(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [1]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [1])
  );
  MUXCY   \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.i_need_mux.carrymux0  (
    .CI(N1),
    .DI(a[0]),
    .S(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [0]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/carry_simple [0])
  );
  FD #(
    .INIT ( 1'b0 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output_1  (
    .C(clk),
    .D(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [0]),
    .Q(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [1])
  );
  FD #(
    .INIT ( 1'b0 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output_2  (
    .C(clk),
    .D(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [1]),
    .Q(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [2])
  );
  FD #(
    .INIT ( 1'b0 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output_3  (
    .C(clk),
    .D(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [2]),
    .Q(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [3])
  );
  FD #(
    .INIT ( 1'b0 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output_4  (
    .C(clk),
    .D(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/sum_simple [3]),
    .Q(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_q.i_simple.qreg/fd/output [4])
  );
  LUT2 #(
    .INIT ( 4'h6 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/Mxor_i_simple_model.halfsum_0_xo<0>1  (
    .I0(a[0]),
    .I1(b[0]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [0])
  );
  LUT2 #(
    .INIT ( 4'h6 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/Mxor_i_simple_model.halfsum_1_xo<0>1  (
    .I0(a[1]),
    .I1(b[1]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [1])
  );
  LUT2 #(
    .INIT ( 4'h6 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/Mxor_i_simple_model.halfsum_2_xo<0>1  (
    .I0(a[2]),
    .I1(b[2]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [2])
  );
  LUT2 #(
    .INIT ( 4'h6 ))
  \U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/Mxor_i_simple_model.halfsum_3_xo<0>1  (
    .I0(a[3]),
    .I1(b[3]),
    .O(\U0/xst_addsub/i_baseblox.i_baseblox_addsub/no_pipelining.the_addsub/i_lut4.i_lut4_addsub/i_simple_model.halfsum [3])
  );

// synthesis translate_on

endmodule

// synthesis translate_off

`ifndef GLBL
`define GLBL

`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;

    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule

`endif

// synthesis translate_on
