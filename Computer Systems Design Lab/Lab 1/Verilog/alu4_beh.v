`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    alu4_beh 
//////////////////////////////////////////////////////////////////////////////////

module alu4_beh(A_in, B_in, SEL_in, Y);

// declare inputs/outputs
input [3:0] A_in;
input [3:0] B_in;
input [1:0] SEL_in;
output [3:0] Y;

// ports that retain values
reg [3:0] Y;

// update design
always @ (A_in or B_in or SEL_in)
begin
	case (SEL_in)
		2'b00: Y = ~A_in;
		2'b01: Y = A_in + B_in;
		2'b10: Y = A_in - B_in;
		2'b11: Y = A_in << 1;
		default: Y = 4'bz;
	endcase
end

endmodule
