`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Module Name:    binary_2_bcd 
//////////////////////////////////////////////////////////////////////////////////

module binary_2_bcd (bin_in, digit_1, digit_2);

	// input / output
	input [6:0] bin_in;
	output [3:0] digit_1;
	output [3:0] digit_2;
	
	// registers
	reg [14:0] buff;
	reg [3:0] digit_1;
	reg [3:0] digit_2;
	
	// update state
	always @ (bin_in)
	begin	
	
		// initialize buffer
		buff = 0;
		buff = buff + bin_in;
		
		repeat (7) // 8 shifts for 2 digit Double Dabble
		begin
		
			if (buff[10:7] > 4) 
			begin
				buff[10:7] = buff[10:7] + 3;
			end
			
			if (buff[14:11] > 4)
			begin
				buff[14:11] = buff[10:7] + 3;
			end
			
			buff = buff << 1;
			
		end
	
		// non-blocking assignments
		digit_1 <= buff[10:7]; 
		digit_2 <= buff[14:11];	
		
	end

endmodule
