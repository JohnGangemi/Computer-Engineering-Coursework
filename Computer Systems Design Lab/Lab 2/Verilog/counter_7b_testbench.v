`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Design Name:   counter_7b
////////////////////////////////////////////////////////////////////////////////

module counter_7b_testbench;

	// Inputs
	reg enable;
	reg reset;
	reg clk;

	// Outputs
	wire [6:0] count_out;

	// Instantiate the Unit Under Test (UUT)
	counter_7b uut (
		.enable(enable), 
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
		enable = 0;
		reset = 0;

		// Wait 10 ns for global reset to finish
		#10;
        
		// test all possible cases of reset and enable	
		enable = 1;
		#10;
		reset = 1;
		#10;
		enable = 0;
		#10;
		reset = 0;
		#10;
		
		// test hold of output when disabling counter
		enable = 1;
		#60;
		enable = 0;
		#30 $finish; // hold for 3 cycles

	end
      
endmodule

