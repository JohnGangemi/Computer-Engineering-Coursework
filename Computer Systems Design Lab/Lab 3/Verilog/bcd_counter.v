`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    bcd_counter 
//////////////////////////////////////////////////////////////////////////////////

module bcd_counter(max_count, clk, run, digit_1, digit_2);

	// input / output
	input [6:0] max_count;
	input clk, run;
	output [3:0] digit_1;
	output [3:0] digit_2;

	// TODO: Wires and registers for interconnect
	reg [6:0] set = 0;
	wire [6:0] counter_to_bcd;

	// Programmable 7-bit counter module
	prog_counter_7b counter (
		.max_count(set), 
		.reset(~run),
		.clk(clk), 
		.count_out(counter_to_bcd)
	);
	
	// Binary-to-BCD Converter
	binary_2_bcd bcd_converter (
		.bin_in(counter_to_bcd),
		.digit_1(digit_1), 
		.digit_2(digit_2)
	);
	
	// update state
	always @ (posedge clk)
	begin

		if (run == 0)
		begin
			set = max_count;
		end
		
	end

endmodule
