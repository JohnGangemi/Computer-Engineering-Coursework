`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:20:42 02/26/2015
// Design Name:   loopback
// Module Name:   E:/CSD LAB/lab6/loop_testbench.v
// Project Name:  lab6
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: loopback
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module loop_testbench;

	// Inputs
	reg [7:0] switches;
	reg rs232_rx;
	reg reset;
	reg clk;

	// Outputs
	wire [7:0] leds;
	wire rs232_tx;

	// Instantiate the Unit Under Test (UUT)
	loopback uut (
		.switches(switches), 
		.leds(leds), 
		.rs232_tx(rs232_tx), 
		.rs232_rx(rs232_rx), 
		.reset(reset), 
		.clk(clk)
	);
	
	// generate 100 MHz system clock
	always begin
		clk = 1'b1;
		#5;
		clk = 1'b0;
		#5;
	end

	initial begin
		// Initialize Inputs
		switches = 8'b00000000;
		rs232_rx = 0;
		reset = 0;

		// Wait 100 ns for global reset to finish
		#20;
        
		// Add stimulus here
		reset = 1;
		switches = 8'b01010101;
		#6000000 $finish;
	end
      
endmodule

