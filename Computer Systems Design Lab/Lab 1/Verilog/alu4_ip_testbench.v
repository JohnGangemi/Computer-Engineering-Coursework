`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Engineer:	John Gangemi
// Design Name:   alu4_ip
////////////////////////////////////////////////////////////////////////////////

module alu4_ip_testbench;

	// Inputs
	reg clk;
	reg [3:0] A_in;
	reg [3:0] B_in;
	reg [1:0] SEL_in;

	// Outputs
	wire [3:0] Y;

	// Instantiate the Unit Under Test (UUT)
	alu4_ip uut (
		.clk(clk), 
		.A_in(A_in), 
		.B_in(B_in), 
		.SEL_in(SEL_in), 
		.Y(Y)
	);
	
	// clock generation
	always begin
		clk = 1'b0;
		#50;
		clk = 1'b1;
		#50;
	end

	initial begin
		// Initialize Inputs
		A_in = 0;
		B_in = 0;
		SEL_in = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		A_in = 6;
		#100;
		
		SEL_in = 1;
		A_in = 2;
		B_in = 3;
		#100;
		A_in = 10;
		B_in = 6;
		#100;
		
		SEL_in = 2;
		A_in = 8;
		B_in = 5;
		#100;
		A_in = 3;
		B_in = 4;
		#100;
		
		SEL_in = 3;
		B_in = 0;
		A_in = 5;
		#100;
		A_in = 7;
		#100 $finish;
	end
      
endmodule

