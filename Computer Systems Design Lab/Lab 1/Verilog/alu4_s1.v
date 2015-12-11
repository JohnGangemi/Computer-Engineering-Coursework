`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    alu4_s1 
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Behavorial Components
//////////////////////////////////////////////////////////////////////////////////

module inverter (a, y);
// declare inputs/outputs
input a;
output y;

// using primitive
not(y,a);

endmodule


module adder (a, b, cin, sum, cout);
// declare inputs/outputs
input a, b, cin;
output sum, cout;

// registers
reg sum, cout;

// update state
always @ (a or b or cin)
begin
	{cout, sum} = a + b + cin; 
end
endmodule


module subtractor (a, b, cin, diff, cout);
// declare inputs/outputs
input a, b, cin;
output diff, cout;

// registers
reg diff, cout, tmp;

// update state
always @ (a or b or cin)
begin
	tmp = ~b + cin;
	{cout, diff} = a + tmp;
end
endmodule


module doubler (a, cin, dbl_out, cout);
// declare inputs/outputs
input a, cin;
output dbl_out, cout;

// registers
reg dbl_out, cout;

// update state
always @ (a or cin)
begin
	// non-blocking assignments
	dbl_out <= cin;
	cout <= a;
end
endmodule


module multiplexer_41 (a, b, c, d, sel, mux_out);
// declare inputs/outputs
input a, b, c, d;
input [1:0] sel;
output mux_out;

// registers
reg mux_out;

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

//////////////////////////////////////////////////////////////////////////////////
// Structural Components
//////////////////////////////////////////////////////////////////////////////////

module alu_slice (a, b, cin, sel, alu_out, cout);
// declare inputs/outputs
input a, b, cin;
input [1:0] sel;
output alu_out, cout;

// interconnects
wire inv__outMux, add__outMux, subtr__outMux, dbl__outMux, add__cryMux, subtr__cryMux, dbl__cryMux;

// design
inverter inv(
	.a(a),
	.y(inv__outMux)
);

adder add(
	.a(a),
	.b(b),
	.cin(cin),
	.sum(add__outMux),
	.cout(add__cryMux)
);

subtractor subtr(
	.a(a),
	.b(b),
	.cin(cin),
	.diff(subtr__outMux),
	.cout(subtr__cryMux)
);

doubler dbl(
	.a(a), 
	.cin(cin), 
	.dbl_out(dbl__outMux), 
	.cout(dbl__cryMux)
);
	
multiplexer_41 out_mux(
	.a(inv__outMux), 
	.b(add__outMux), 
	.c(subtr__outMux), 
	.d(dbl__outMux), 
	.sel(sel), 
	.mux_out(alu_out)
);
	
multiplexer_41 carry_mux(
	.a(1'b0), 
	.b(add__cryMux), 
	.c(subtr__cryMux), 
	.d(dbl__cryMux), 
	.sel(sel), 
	.mux_out(cout)
);
endmodule


module alu4_s1(A_in, B_in, SEL_in, Y);
// declare inputs/outputs
input [3:0] A_in;
input [3:0] B_in;
input [1:0] SEL_in;
output [3:0] Y;

// interconnects
wire slice1__slice2, slice2__slice3, slice3__slice4;

// design

// LSB
alu_slice slice1(
	.a(A_in[0]), 
	.b(B_in[0]), 
	.cin(~ SEL_in[0]), // 'carry in' is inverse of S0 (fig1)
	.sel(SEL_in), 
	.alu_out(Y[0]), 
	.cout(slice1__slice2)
);

alu_slice slice2(
	.a(A_in[1]), 
	.b(B_in[1]),  
	.cin(slice1__slice2), 
	.sel(SEL_in), 
	.alu_out(Y[1]), 
	.cout(slice2__slice3)
);

alu_slice slice3(
	.a(A_in[2]), 
	.b(B_in[2]), 
	.cin(slice2__slice3), 
	.sel(SEL_in), 
	.alu_out(Y[2]), 
	.cout(slice3__slice4)
);

// MSB
alu_slice slice4(
	.a(A_in[3]), 
	.b(B_in[3]),  
	.cin(slice3__slice4), 
	.sel(SEL_in), 
	.alu_out(Y[3]), 
	.cout() // disregard 'carry out'
);
endmodule
