`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:11:29 02/19/2015
// Design Name:   GCD_FSMD
// Module Name:   E:/CSD LAB/lab05/gcd_testbench.v
// Project Name:  lab05
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: GCD_FSMD
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module gcd_testbench;

	// Inputs
	reg [3:0] x;
	reg [3:0] y;
	reg start;
	reg reset; // active low
	reg user_clk;

	// Outputs
	wire [3:0] gcd_out;
	wire done;

	// Instantiate the Unit Under Test (UUT)
	GCD_FSMD uut (
		.x(x), 
		.y(y), 
		.start(start), 
		.reset(reset), 
		.user_clk(user_clk), 
		.gcd_out(gcd_out), 
		.done(done)
	);

	always begin
		user_clk = 1'b0;
		#5;
		user_clk = 1'b1;
		#5;
	end

	initial begin
		// Initialize Inputs
		x = 0;
		y = 0;
		start = 0;
		reset = 1;

		// Wait 100 ns for global reset to finish
		#10;
        
		// Add stimulus here
		
		/*
		x = 8;
		y = 4;
		#10;
		start = 1;
		#120; 
		reset = 0;
		#10 $finish;
		*/		
		
		/*
		x = 14;
		y = 7;
		#10;
		start = 1;
		#120; 
		reset = 0;
		#10 $finish;
		*/
		
		/*
		x = 9;
		y = 6;
		#10;
		start = 1;
		#120; 
		reset = 0;
		#10 $finish;
		*/
		
		/*
		x = 3;
		y = 1;
		#10;
		start = 1;
		#180; 
		reset = 0;
		#10 $finish;
		*/
		
		/*
		x = 4;
		y = 4;
		#10;
		start = 1;
		#80; 
		reset = 0;
		#10 $finish;
		*/
		
		x = 4;
		y = 4;
		start = 1;
		#80;
		y = 2;
		#100;
		reset = 0;
		#10 $finish;
	end
      
endmodule

