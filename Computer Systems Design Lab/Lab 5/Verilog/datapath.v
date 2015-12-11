`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ISIS
// Create Date:    15:08:59 02/17/2015 
// Module Name:    datapath 
//////////////////////////////////////////////////////////////////////////////////

module datapath(x_in, y_in, x_ld, y_ld, x_sel, y_sel, d_ld, rst, clk, x_ne_y, x_lt_y, d_out);
	
	// input / output
	input [3:0]x_in;
	input [3:0]y_in;
	input x_ld, y_ld, x_sel, y_sel, d_ld, rst, clk;
	
	output x_ne_y, x_lt_y;
	output [3:0]d_out;
	
	// interconnects
	wire [3:0]xmux_to_xreg;
	wire [3:0]ymux_to_yreg; 
	wire [3:0]xminy_to_xmux; 
	wire [3:0]yminx_to_ymux;
	wire [3:0]xreg_to_arith;
	wire [3:0]yreg_to_arith;
	
	// instances
	mux2to1 x_mux(
		.a(x_in),
		.b(xminy_to_xmux),
		.sel(x_sel),
		.out(xmux_to_xreg)
	);
	
	mux2to1 y_mux(
		.a(y_in),
		.b(yminx_to_ymux),
		.sel(y_sel),
		.out(ymux_to_yreg)
	);
	
	register x_reg(
		.in(xmux_to_xreg),
		.enb(x_ld),
		.rst(rst),
		.clk(clk),
		.out(xreg_to_arith)
	);
	
	register y_reg(
		.in(ymux_to_yreg),
		.enb(y_ld),
		.rst(rst),
		.clk(clk),
		.out(yreg_to_arith)
	);
	
	register d_reg(
		.in(xreg_to_arith),
		.enb(d_ld),
		.rst(rst),
		.clk(clk),
		.out(d_out)
	);

	notEqual x_notEqual_y(
		.x(xreg_to_arith),
		.y(yreg_to_arith),
		.out(x_ne_y)
	);
	
	lessThan x_lessThan_y(
		.x(xreg_to_arith),
		.y(yreg_to_arith),
		.out(x_lt_y)
	);
	
	subtract x_minus_y(
		.minuend(xreg_to_arith),
		.subtrahend(yreg_to_arith),
		.difference(xminy_to_xmux)
	);
	
	subtract y_minus_x(
		.minuend(yreg_to_arith),
		.subtrahend(xreg_to_arith),
		.difference(yminx_to_ymux)
	);
endmodule

module subtract(minuend, subtrahend, difference);
	input [3:0]minuend;
	input [3:0]subtrahend;
	output reg [3:0]difference;
	
	always @ (*) begin
		difference = minuend - subtrahend;
	end
endmodule

module lessThan(x, y, out);
	input [3:0]x;
	input [3:0]y;
	output reg out;
	
	always @ (*) begin
		if (x < y)
			out = 1'b1;
		else
			out = 1'b0;
	end
endmodule

module notEqual(x, y, out);
	input [3:0]x;
	input [3:0]y;
	output reg out;
	
	always @ (*) begin
		if (x != y)
			out = 1'b1;
		else
			out = 1'b0;
	end
endmodule

module register(in, enb, rst, clk, out);
	input [3:0]in;
	input enb, rst, clk;
	output reg [3:0]out = 4'b0000; // initialize to zero
	
	always @ (negedge clk) begin
		if (rst)
			out = 4'b0000;
		else if (enb)
			out = in;
	end
endmodule

module mux2to1(a, b, sel, out);
	input [3:0]a;
	input [3:0]b;
	input sel;
	output reg [3:0]out;
	
	always @ (*) begin
		if (sel)
			out = b;
		else
			out = a;
	end
endmodule
