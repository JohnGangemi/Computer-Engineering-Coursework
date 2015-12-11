`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    counter_7b 
//////////////////////////////////////////////////////////////////////////////////

module counter_7b (enable, reset, clk, count_out);

	// input / output
	input enable, reset, clk;
	output [6:0] count_out;
	
	// registers
	reg [6:0] count_out = 0;

	// update state 
	always @ (posedge clk)
	begin

		if (reset) // synchronous reset takes precedence
		begin 
			count_out = 0;
		end 
		
		else if (enable) // increment counter
		begin 
			count_out = count_out + 1;
		end	
		
	end
  
endmodule
