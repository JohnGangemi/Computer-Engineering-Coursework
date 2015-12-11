`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ISIS
// Create Date:    15:08:47 02/17/2015 
// Module Name:    controller 
//////////////////////////////////////////////////////////////////////////////////

module controller(start, x_ne_y, x_lt_y, rst, clk, x_ld, y_ld, d_ld, x_sel, y_sel, done);

	// input / output
	input start, x_ne_y, x_lt_y, rst, clk;
	output reg x_ld, y_ld, d_ld, x_sel, y_sel;
	output reg done = 1'b0; // initialize to zero

	// state encoding
	parameter s1 	= 4'b0000;
	parameter s2 	= 4'b0001;
	parameter s2J 	= 4'b0010;
	parameter s3 	= 4'b0011;
	parameter s4 	= 4'b0100;
	parameter s5 	= 4'b0101;
	parameter s6 	= 4'b0110;
	parameter s7 	= 4'b0111;
	parameter s8 	= 4'b1000;
	parameter s6J 	= 4'b1001;
	parameter s5J	= 4'b1010;
	parameter s9 	= 4'b1011;
	parameter s1J 	= 4'b1100;

	// registers
	reg [3:0]state = s1;
	
	// update output
	always @ (state) begin
		case (state)

			s3: begin
				x_ld = 1'b1;
				x_sel = 1'b0;
				y_ld = 1'b0;
				y_sel = 1'b0;
				d_ld = 1'b0;
			end
				
			s4: begin
				x_ld = 1'b0;
				x_sel = 1'b0;
				y_ld = 1'b1;
				y_sel = 1'b0;
				d_ld = 1'b0;
			end
			
			s7: begin
				x_ld = 1'b0;
				x_sel = 1'b0;
				y_ld = 1'b1;
				y_sel = 1'b1;
				d_ld = 1'b0;
			end
			
			s8: begin
				x_ld = 1'b1;
				x_sel = 1'b1;
				y_ld = 1'b0;
				y_sel = 1'b0;
				d_ld = 1'b0;
			end
			
			s9: begin
				x_ld = 1'b0;
				x_sel = 1'b0;
				y_ld = 1'b0;
				y_sel = 1'b0;
				d_ld = 1'b1;
			end
			
			default: begin
				x_ld = 1'b0;
				x_sel = 1'b0;
				y_ld = 1'b0;
				y_sel = 1'b0;
				d_ld = 1'b0;
			end
			
		endcase
	end
	
	// update state
	always @ (posedge clk) begin
		if (rst) begin
			state <= s1;
			done <= 1'b0;
		end else
			case (state)
			
				s1: begin
					state <= s2;
					done <= done;
				end
				
				s2: begin
					if (start)
						state <= s3;
					else
						state <= s2J;
					done <= done;
				end
				
				s2J: begin
					state <= s2;
					done <= done;
				end
				
				s3: begin
					state <= s4;
					done <= done;
				end
				
				s4: begin
					state <= s5;
					done <= done;
				end
				
				s5: begin
					if (x_ne_y)
						state <= s6;
					else
						state <= s9;
					done <= done;
				end
				
				s6: begin
					if (x_lt_y)
						state <= s7;
					else
						state <= s8;
					done <= done;
				end
				
				s7: begin
					state <= s6J;
					done <= done;
				end
				
				s8: begin
					state <= s6J;
					done <= done;
				end
				
				s6J: begin
					state <= s5J;
					done <= done;
				end
				
				s5J: begin
					state <= s5;
					done <= done;
				end
				
				s9: begin
					state <= s1J;
					done <= 1'b1; // GCD has been computed
				end
				
				s1J: begin
					state <= s1;
					done <= done;
				end
				
				default: begin
					state <= 4'bxxxx;
					done <= 1'b0;
				end
				
			endcase
	end
endmodule
