`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ISIS
// Create Date:    22:15:50 02/17/2015 
// Module Name:    GCD_FSMD 
//////////////////////////////////////////////////////////////////////////////////

module GCD_FSMD(x, y, start, reset, user_clk, gcd_out, done);

	// input / output
	input start, reset, user_clk; // active-low reset!
	input [3:0]x;
	input [3:0]y;
	output done;
	output [3:0]gcd_out;

	// interconnects
	wire start_cln, xney, xlty, xld, yld, dld, xsel, ysel;
	
	// components
	debounce start_btn(
		.reset(~reset), // negate for final design
		.clk(user_clk),
		.noisy(start),
		.clean(start_cln)
	);
	
	controller mproc(
		.start(start_cln),
		.x_ne_y(xney),
		.x_lt_y(xlty),
		.rst(~reset), // negate for final design
		.clk(user_clk),
		.x_ld(xld),
		.y_ld(yld),
		.d_ld(dld),
		.x_sel(xsel),
		.y_sel(ysel),
		.done(done)
	);
	
	datapath data(
		.x_in(x), 
		.y_in(y), 
		.x_ld(xld), 
		.y_ld(yld), 
		.x_sel(xsel), 
		.y_sel(ysel), 
		.d_ld(dld), 
		.rst(~reset), // negate for final design
		.clk(user_clk), 
		.x_ne_y(xney), 
		.x_lt_y(xlty), 
		.d_out(gcd_out)
	);
endmodule

// module adapted from "debounce.v" created/provided by Massachusetts Institute of Technology
// http://web.mit.edu/6.111/www/f2005/code/jtag2mem_6111/debounce.v.html 
module debounce (reset, clk, noisy, clean);

	// inputs / outputs
	input reset, clk, noisy;
   output reg clean;
	
	// registers
	reg [19:0] count;
   reg tmp;
	
	// parameters
   parameter MAX_COUNT = 1000000; // .01 sec with 100 MHz clock (clock frequency x .01 sec)

	// sequential logic
   always @(posedge clk)
		if (reset) begin 
			tmp <= noisy; 
			clean <= noisy; 
			count <= 1'b0; 
		end else if (noisy != tmp) begin 
			tmp <= noisy; 
			count <= 1'b0; 
		end else if (count == MAX_COUNT) 
			clean <= tmp;
		else 
			count <= count + 1'b1;			
endmodule
