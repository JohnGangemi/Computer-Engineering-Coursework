`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Design Name:   binary_2_bcd
////////////////////////////////////////////////////////////////////////////////

module binary_2_bcd_testbench;

	// Inputs
	reg [6:0] bin_in;

	// Outputs
	wire [3:0] digit_1;
	wire [3:0] digit_2;

	// Instantiate the Unit Under Test (UUT)
	binary_2_bcd uut (
		.bin_in(bin_in), 
		.digit_1(digit_1), 
		.digit_2(digit_2)
	);

	initial begin
		// Initialize Inputs
		bin_in = 0;

		// Wait 10 ns for global reset to finish
		#10;
        
		// convert binary numbers from 0-99
		bin_in = 12;
		#10;
		bin_in = 25;
		#10;
		bin_in = 37;
		#10;
		bin_in = 49;
		#10;
		bin_in = 64;
		#10;
		bin_in = 81;
		#10;
		bin_in = 99;
		#10;
		
		// should show erroneous value
		bin_in = 100;
		#10 $finish;
		
	end
      
endmodule

