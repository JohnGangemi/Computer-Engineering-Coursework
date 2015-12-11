`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
// Module Name:    soda_machine_wrapper 
//////////////////////////////////////////////////////////////////////////////////

module soda_machine_wrapper(quarter, nickel, dime, soda, diet, soda_given, diet_given, change_count, reset, clk);

	// Inputs. The reset input is to be tied to the red RESET button on the FPGA.
	//That red button is ***ACTIVE LOW***, so the value is normally 1; pressing it results in 0
	input quarter, nickel, dime, soda, diet, reset, clk;

	output soda_given, diet_given; // Map each to an LED
	output [2:0] change_count; // Map to three LEDs. 

	// Wires to connect Soda FSM to the capture module
	wire change, give_soda, give_diet;
	
	// Wires to connect module inputs to Soda FSM and Soda Capture
	wire cln_qtr, cln_dme, cln_nkl, cln_soda, cln_diet;
	
	// Debounce external push-button inputs
	debounce btn_qtr (.reset(reset), .clk(clk), .noisy(quarter), .clean(cln_qtr));
	debounce btn_dme (.reset(reset), .clk(clk), .noisy(dime), .clean(cln_dme));
	debounce btn_nkl (.reset(reset), .clk(clk), .noisy(nickel), .clean(cln_nkl));
	debounce btn_soda (.reset(reset), .clk(clk), .noisy(soda), .clean(cln_soda));
	debounce btn_diet (.reset(reset), .clk(clk), .noisy(diet), .clean(cln_diet));

	// Your FSM module - fill in with name of your soda machine top module
	soda_machine soda_fsm(	.quarter(cln_qtr),.nickel(cln_nkl),.dime(cln_dme),.soda(cln_soda),.diet(cln_diet),
									.change(change),.give_soda(give_soda),.give_diet(give_diet),
									.reset(reset), .clk(clk));
								
	// FSM Output capture module. 
	// ** NOTE ** Our reset line is active-low, but the fsmcap expects active-high. Therefore, we pass
	//the inverted reset (~reset) as the reset signal to the fsmcap.
	soda_machine_capture fsmcap(	.give_change(change),.give_diet(give_diet),.give_soda(give_soda),
											.soda_given(soda_given),.diet_given(diet_given),.change_count(change_count),
											.reset(~reset),.clk(clk));

endmodule

module soda_machine_capture(give_change, give_diet, give_soda, reset, change_count, soda_given, diet_given, clk);

	input give_change, give_diet, give_soda, reset, clk;

	// Outputs the number of nickels returned as change.
	output reg [2:0] change_count;
	output reg soda_given;
	output reg diet_given;

	// Asynchronous, preemptive, active-high reset.

	always @(negedge clk or posedge reset)
	begin
		if(reset) begin
			change_count = 0;
			soda_given = 0;
			diet_given = 0;
		end else begin
			if(give_change) change_count = change_count + 1'b1;
			else if(give_soda) begin 
				soda_given = 1;
				change_count = 0;
				diet_given = 0;
			end else if(give_diet) begin
				diet_given = 1;
				change_count = 0;
				soda_given = 0;
			end
		end
	end

endmodule

// module adapted from "debounce.v" created/provided by Massachusetts Institute of Technology
// http://web.mit.edu/6.111/www/f2005/code/jtag2mem_6111/debounce.v.html 
module debounce (reset, clk, noisy, clean);

	// inputs / outputs
	input reset, clk, noisy; // active-low reset for FPGA board
   output reg clean;
	
	// registers
	reg [19:0] count;
   reg tmp;
	
	// parameters
   parameter MAX_COUNT = 1000000; // .01 sec with 100 MHz clock (clock frequency x .01 sec)

	// sequential logic
   always @(posedge clk)
		if (reset == 0) begin 
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
