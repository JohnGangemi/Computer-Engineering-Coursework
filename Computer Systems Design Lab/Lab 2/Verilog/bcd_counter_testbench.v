`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Design Name:   bcd_counter
////////////////////////////////////////////////////////////////////////////////

module bcd_counter_testbench;

	// Inputs
	reg [6:0] max_count;
	reg clk;
	reg run;

	// Outputs
	wire [3:0] digit_1;
	wire [3:0] digit_2;

	// Instantiate the Unit Under Test (UUT)
	bcd_counter uut (
		.max_count(max_count), 
		.clk(clk), 
		.run(run), 
		.digit_1(digit_1), 
		.digit_2(digit_2)
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
		run = 0;

		// Wait 10 ns for global reset to finish
		#10;
        
		// change max_count multiple times when run = 0
		max_count = 35;
		#10;
		max_count = 16;
		#10;
		max_count = 4; 
		#10;
		
		// counter should stop at 4
		run = 1; 
		#50; 
		
		// counter should not exceed 99
		run = 0;
		max_count = 101; 
		#10;
		run = 1;
		#1020;
		
		// changes to max_count should be ignored 
		// when run == 1
		run = 0;
		max_count = 6; // desired max_count
		#10;
		
		run = 1;
		#10;
		max_count = 59;
		#10;
		max_count = 72;
		#10;
		#40 $finish;

	end
      
endmodule

