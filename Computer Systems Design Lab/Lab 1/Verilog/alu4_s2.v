`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    alu4_s2 
//////////////////////////////////////////////////////////////////////////////////

module inverter_4b (a, y);
// declare inputs/outputs
input [3:0] a;
output [3:0] y;

assign y = ~a;

endmodule


module adder_4b (a, b, sum);
// declare inputs/outputs
input [3:0] a;
input [3:0] b;
output [3:0] sum;

// registers
reg [3:0] sum;

// update state
always @ (a or b)
begin
	sum = a + b;
end
endmodule


module subtractor_4b (a, b, diff);
// declare inputs/outputs
input [3:0] a;
input [3:0] b;
output [3:0] diff;

// registers
reg [3:0] diff;

// update state
always @ (a or b)
begin
	diff = a - b;
end
endmodule


module doubler_4b (a, y);
// declare inputs/outputs
input [3:0] a;
output [3:0] y;

// registers
reg [3:0] y;

// update state
always @ (a)
begin
	y = a << 1;
end
endmodule


module multiplexer_4b (a, b, c, d, sel, mux_out);
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


module alu4_s2(A_in, B_in, SEL_in, Y);
// declare inputs/outputs
input [3:0] A_in;
input [3:0] B_in;
input [1:0] SEL_in;
output [3:0] Y;

// interconnects
wire [3:0] inv__mux; 
wire [3:0] add__mux; 
wire [3:0] subtr__mux; 
wire [3:0] dbl__mux;

// design
inverter_4b inv(
	.a(A_in),
	.y(inv__mux)
);

adder_4b add(
	.a(A_in),
	.b(B_in), 
	.sum(add__mux)
);

subtractor_4b subtr(
	.a(A_in),
	.b(B_in), 
	.diff(subtr__mux)
);

doubler_4b dbl(
	.a(A_in),
	.y(dbl__mux)
);

multiplexer_4b mux(
	.a(inv__mux), 
	.b(add__mux), 
	.c(subtr__mux), 
	.d(dbl__mux), 
	.sel(SEL_in), 
	.mux_out(Y)
);
endmodule
