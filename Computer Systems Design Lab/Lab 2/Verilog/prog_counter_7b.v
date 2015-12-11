`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi  
// Module Name:    prog_counter_7b 
//////////////////////////////////////////////////////////////////////////////////

module prog_counter_7b (max_count, reset, clk, count_out);

	// input / output
	input [6:0] max_count;
	input reset, clk;
	output [6:0] count_out;

	// registers
	reg enb = 0;
	
	// 7-bit counter instance
	counter_7b counter (
		.enable(enb),
		.reset(reset),
		.clk(clk),
		.count_out(count_out)
	);

	// update state
	always @ (negedge clk)
	begin
	
		if (count_out < max_count && count_out < 99) // stop at max_count and do not exceed max value 99
		begin
			enb = 1;
		end 

		else
		begin
			enb = 0;
		end
		
	end
	
endmodule
