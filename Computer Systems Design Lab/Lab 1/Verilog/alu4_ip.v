`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    alu4_ip 
//////////////////////////////////////////////////////////////////////////////////
module mux_4b (a, b, c, d, sel, mux_out);
// declare inputs/outputs
// declare inputs/outputs
input [3:0] a;
input [3:0] b;
input [3:0] c;
input [3:0] d;
input [1:0] sel;
output [3:0] mux_out;

// registers
reg [3:0] mux_out;

// update state
always @ (a or b or c or d or sel)
begin
	case (sel)
		2'b00: mux_out = a;
		2'b01: mux_out = b;
		2'b10: mux_out = c;
		2'b11: mux_out = d;
	endcase
end 
endmodule

module alu4_ip(clk, A_in, B_in, SEL_in, Y);
// declare inputs/outputs
input clk;
input [3:0] A_in;
input [3:0] B_in;
input [1:0] SEL_in;
output [3:0] Y;

// interconnects
wire [3:0] add__mux;
wire [3:0] subtr__mux;

// design
adder_4b_ip add (
  .a(A_in), // input [3 : 0] a
  .b(B_in), // input [3 : 0] b
  .clk(clk), // input clk
  .s(add__mux) // output [3 : 0] s
);

subtr_4b_ip subtr (
  .a(A_in), // input [3 : 0] a
  .b(B_in), // input [3 : 0] b
  .clk(clk), // input clk
  .s(subtr__mux) // output [3 : 0] s
);

mux_4b mux (
	.a(~ A_in), 
	.b(add__mux), 
	.c(subtr__mux), 
	.d(A_in << 1), 
	.sel(SEL_in), 
	.mux_out(Y)
);
endmodule
