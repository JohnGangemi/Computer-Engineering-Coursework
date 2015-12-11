`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Design Name:   prog_counter_7b
////////////////////////////////////////////////////////////////////////////////

module prog_counter_7b_testbench;

	// Inputs
	reg [6:0] max_count;
	reg reset;
	reg clk;

	// Outputs
	wire [6:0] count_out;

	// Instantiate the Unit Under Test (UUT)
	prog_counter_7b uut (
		.max_count(max_count), 
		.reset(reset), 
		.clk(clk), 
		.count_out(count_out)
	);

	// clock generation for 100MHz
	always begin
		clk = 1'b0;
		#5;
		clk = 1'b1;
		#5;
	end
	
	initial begin
		// Initialize Inputs
		max_count = 0;
		reset = 0;

		// Wait 10 ns for global reset to finish
		#10;
        
		// counter should stop when reaching max_count
		max_count = 14;
		#160; // wait two extra cycles
		
		reset = 1;
		max_count = 7;
		#10;
		
		reset = 0;
		#90; // wait two extra cycles
		
		// counter should not exceed 99
		max_count = 106;
		#1080 $finish; 
	end
      
endmodule

