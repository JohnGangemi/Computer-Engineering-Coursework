`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Design Name:   soda_machine
// Module Name:   E:/CSD LAB/lab04/soda_fsm_test.v
////////////////////////////////////////////////////////////////////////////////

module soda_fsm_test;

	// Inputs
	reg quarter;
	reg nickel;
	reg dime;
	reg soda;
	reg diet;
	reg reset; // active - low
	reg clk;

	// Outputs
	wire change;
	wire give_soda;
	wire give_diet;

	// Instantiate the Unit Under Test (UUT)
	soda_machine uut (
		.quarter(quarter), 
		.nickel(nickel), 
		.dime(dime), 
		.soda(soda), 
		.diet(diet), 
		.change(change), 
		.give_soda(give_soda), 
		.give_diet(give_diet), 
		.reset(reset), 
		.clk(clk)
	);

	// generate system clock (100 MHz)
	always begin
		clk = 0;
		#5;
		clk = 1;
		#5;
	end

	initial begin
		// Initialize Inputs
		quarter = 0;
		dime = 0;
		nickel = 0;
		soda = 0;
		diet = 0;
		reset = 0; 

		// Wait 10 ns for global reset to finish
		#10;
        
		// no change given (100ns)	
		/*reset = 1;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		quarter = 1;
		#10;
		quarter = 0;
		#10;
		diet = 1;
		#10;
		diet = 0;
		#20 $finish;*/
		
		// 5 cents in change given (110ns)		
		/*reset = 1;
		#10;
		quarter = 1;
		#10;
		quarter = 0;
		#10;
		quarter = 1;
		#10;
		quarter = 0;
		#10;
		soda = 1;
		#10;
		soda = 0;
		#50 $finish;*/
		
		// 20 cents in change given (230ns)		
		/*reset = 1;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		quarter = 1;
		#10;
		quarter = 0;
		#10;
		soda = 1;
		#10;
		soda = 0;
		#110 $finish;*/
		
		// testing inputs (160ns)
		reset = 1;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		dime = 1;
		#10;
		dime = 0;
		#10;
		soda = 1;
		#20;
		soda = 0;
		diet = 1;
		#10;
		diet = 0;
		quarter = 1;
		#30;
		quarter = 0;
		#10;
		diet = 1;
		#10;
		diet = 0;
		#30 $finish;
	end
      
endmodule

