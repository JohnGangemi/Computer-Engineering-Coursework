`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
// Module Name:    soda_machine 
//////////////////////////////////////////////////////////////////////////////////

module soda_machine(quarter, nickel, dime, soda, diet, change, give_soda, give_diet, reset, clk);

	// inputs / outputs
	input quarter, nickel, dime, soda, diet, reset, clk; // reset is active-low
	output reg change, give_soda, give_diet;
	
	// registers
	reg [4:0] state = cents_0;
	reg [4:0] return_state = cents_0;
	
	// state encoding
	parameter cents_0    	= 5'b00000;
   parameter cents_5    	= 5'b00001;
   parameter cents_10   	= 5'b00010;
   parameter cents_15   	= 5'b00011;
   parameter cents_20   	= 5'b00100;
   parameter cents_25   	= 5'b00101;
   parameter cents_30   	= 5'b00110;
   parameter cents_35   	= 5'b00111;
   parameter cents_40   	= 5'b01000;
   parameter cents_45   	= 5'b01001;
   parameter cents_50   	= 5'b01010;
   parameter cents_55   	= 5'b01011;
   parameter cents_60   	= 5'b01100;
   parameter cents_65   	= 5'b01101;
   parameter change_5c  	= 5'b01110;
   parameter change_10c 	= 5'b01111;
	parameter change_15c 	= 5'b10000;
	parameter change_20c 	= 5'b10001;
	parameter vend_soda  	= 5'b10010;
	parameter vend_diet  	= 5'b10011;
	parameter render_change	= 5'b10100;
	parameter wait_state		= 5'b10101;

	// update output
	always @ (*) begin
		case (state)
			vend_soda: begin
				give_soda = 1'b1;
				give_diet = 1'b0;
				change = 1'b0;
			end
			vend_diet: begin
				give_soda = 1'b0;
				give_diet = 1'b1;
				change = 1'b0;
			end
			render_change: begin
				give_soda = 1'b0;
				give_diet = 1'b0;
				change = 1'b1;
			end
			default: begin
				give_soda = 1'b0;
				give_diet = 1'b0;
				change = 1'b0;
			end
		endcase
	end
	
	// update state
	always @ (posedge clk) begin
		if (reset == 0)
			state <= cents_0;
		else
			case (state)
				cents_0: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_5;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_10;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_25;
					end
				end
				cents_5: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_10;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_15;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_30;
					end
				end				
				cents_10: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_15;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_20;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_35;
					end
				end				
				cents_15: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_20;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_25;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_40;
					end
				end				
				cents_20: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_25;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_30;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_45;
					end
				end				
				cents_25: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_30;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_35;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_50;
					end
				end				
				cents_30: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_35;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_40;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_55;
					end
				end				
				cents_35: begin
					if (!quarter && !dime && nickel) begin 
						state <= wait_state;
						return_state <= cents_40;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_45;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_60;
					end
				end		
				cents_40: begin
					if (!quarter && !dime && nickel) begin
						state <= wait_state;
						return_state <= cents_45;
					end else if (!quarter && dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_50;
					end else if (quarter && !dime && !nickel) begin
						state <= wait_state;
						return_state <= cents_65;
					end
				end				
				cents_45: begin
					if (soda && !diet) begin
						state <= vend_soda;
						return_state <= cents_0;
					end else if (!soda && diet) begin
						state <= vend_diet;
						return_state <= cents_0;
					end
				end				
				cents_50: begin
					if (soda && !diet) begin
						state <= vend_soda;
						return_state <= change_5c;
					end else if (!soda && diet) begin
						state <= vend_diet;
						return_state <= change_5c;
					end
				end				
				cents_55: begin
					if (soda && !diet) begin
						state <= vend_soda;
						return_state <= change_10c;
					end else if (!soda && diet) begin
						state <= vend_diet;
						return_state <= change_10c;
					end
				end				
				cents_60: begin
					if (soda && !diet) begin
						state <= vend_soda;
						return_state <= change_15c;
					end else if (!soda && diet) begin
						state <= vend_diet;
						return_state <= change_15c;
					end
				end				
				cents_65: begin
					if (soda && !diet) begin
						state <= vend_soda;
						return_state <= change_20c;
					end else if (!soda && diet) begin
						state <= vend_diet;
						return_state <= change_20c;
					end
				end				
				change_5c: begin
					state <= render_change;
					return_state <= cents_0;
				end
				change_10c: begin
					state <= render_change;
					return_state <= change_5c;
				end
				change_15c: begin
					state <= render_change;
					return_state <= change_10c;
				end
				change_20c: begin
					state <= render_change;
					return_state <= change_15c;
				end
				vend_soda: begin
					state <= return_state;
				end
				vend_diet: begin
					state <= return_state;
				end
				render_change: begin
					state <= return_state;
				end
				wait_state: begin
					if (!quarter && !nickel && !dime)
						state <= return_state;
				end
				default: begin
					state <= 1'bx;
				end
			endcase
	end

endmodule
