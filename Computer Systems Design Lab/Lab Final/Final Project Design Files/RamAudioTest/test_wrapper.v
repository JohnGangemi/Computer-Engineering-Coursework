`timescale 1ns / 1ps

module test_wrapper(
    input reset,
    input clock,
    input play_sw,
    input up_btn, // LOC N4
	input dwn_btn, // LOC P3
	input sel_btn, // LOC F5
	input lft_btn,	// LOC P4
	input rht_btn, // LOC F6
    output[7:0] leds,
    output reg lcd_enb, 
    output reg lcd_rs, 
    output reg lcd_rw,
    output reg[3:0] lcd_data,
  
    // RAM
    output  hw_ram_rasn,
    output  hw_ram_wen,
    inout   hw_ram_ldqs_n,    
    output  hw_ram_cke,
    output  hw_ram_casn,
    output  [2:0] hw_ram_ba,
    output  hw_ram_udm, 
    output  hw_ram_odt,
    inout   hw_ram_udqs_p,   
    output  hw_ram_ldm,        
    inout   hw_ram_udqs_n,   
    output  hw_ram_ck,
    output  [12:0] hw_ram_ad,
    inout   hw_ram_ldqs_p,     
    output  hw_ram_ckn,
    inout   [15:0] hw_ram_dq, 
    inout   pin_rzq_ref,       
    inout   pin_zio_ref,       
    
    // AUDIO
    input   ac97_sdata_in,
    output  audio_reset_b,
    output  ac97_sdata_out,
    output  ac97_synch,
    input   ac97_bit_clock
);

// RAM
wire ram_rdy; 
wire rd_data_pres; 
wire write_enable; 
wire read_request; 
wire read_ack;
wire [7:0] data_from_ram;
wire [7:0] data_to_ram;
wire ram_clkout;
wire [25:0] ram_address;

// AC97
wire audio_rdy;

// LCD 
reg lcd_wrt_ack;
wire fsm_wrt_req;
wire[7:0] lcd_nxt_state;
wire[4:0] jesus_juice;

// PicoBlaze Data Lines
wire [7:0]pb_port_id;
wire [7:0]pb_out_port;
reg [7:0]pb_in_port;
wire pb_read_strobe;
wire pb_write_strobe;

// PicoBlaze CPU Control Wires
wire pb_reset;
wire pb_interrupt;
wire pb_int_ack;

// Disable interrupt by assigning 0 to interrupt
assign pb_interrupt = 1'b0;

// Debounce external push-button inputs
wire cln_upBtn;
wire cln_dwnBtn;
wire cln_selBtn;
wire cln_lftBtn;
wire cln_rhtBtn;

// instances
debounce up_button (.reset(reset), .clk(ram_clkout), .noisy(up_btn), .clean(cln_upBtn));
debounce dwn_button (.reset(reset), .clk(ram_clkout), .noisy(dwn_btn), .clean(cln_dwnBtn));
debounce sel_button (.reset(reset), .clk(ram_clkout), .noisy(sel_btn), .clean(cln_selBtn));
debounce lft_button (.reset(reset), .clk(ram_clkout), .noisy(lft_btn), .clean(cln_lftBtn));
debounce rht_button (.reset(reset), .clk(ram_clkout), .noisy(rht_btn), .clean(cln_rhtBtn));

picoblaze CPU (
    .port_id 			(pb_port_id),
    .read_strobe 		(pb_read_strobe),
    .in_port 			(pb_in_port),
    .write_strobe 		(pb_write_strobe),
    .out_port			(pb_out_port),
    .interrupt			(pb_interrupt),
    .interrupt_ack		(),
    .reset				(~reset),
    .clk				(ram_clkout)
);	

lcd_fsm LCD (
    .clk                (ram_clkout),
    .reset              (~reset),
    .play_sw            (play_sw),
    .mov_up             (cln_upBtn), 
    .mov_dwn            (cln_dwnBtn), 
    .sel                (cln_selBtn), 
    .vol_dwn            (cln_lftBtn), 
    .vol_up             (cln_rhtBtn),
    .wrt_ack            (lcd_wrt_ack),
    .audio_rdy          (audio_rdy),
    .data_present_bro   (rd_data_pres),
    .ram_rdy            (ram_rdy),
    .wrt_req            (fsm_wrt_req),
    .write_enb          (write_enable),
    .read_req           (read_request),
    .read_ack           (read_ack),
    .lcd_state          (lcd_nxt_state), 
    .vol_level          (jesus_juice),
    .addr               (ram_address),
    .leds               (leds)
);

ram_interface_wrapper ram_instance(
        
        .address            ( ram_address     ), 
        .data_in            ( data_to_ram     ), 
        .write_enable       ( write_enable    ), 
        .read_request       ( read_request    ), 
        .read_ack           ( read_ack        ), 
        .data_out           ( data_from_ram   ), 
        .reset              ( ~reset          ), 
        .clk                ( clock           ), 
        .hw_ram_rasn        ( hw_ram_rasn     ), 
        .hw_ram_casn        ( hw_ram_casn     ),
        .hw_ram_wen         ( hw_ram_wen      ), 
        .hw_ram_ba          ( hw_ram_ba       ), 
        .hw_ram_udqs_p      ( hw_ram_udqs_p   ), 
        .hw_ram_udqs_n      ( hw_ram_udqs_n   ), 
        .hw_ram_ldqs_p      ( hw_ram_ldqs_p   ), 
        .hw_ram_ldqs_n      ( hw_ram_ldqs_n   ), 
        .hw_ram_udm         ( hw_ram_udm      ), 
        .hw_ram_ldm         ( hw_ram_ldm      ), 
        .hw_ram_ck          ( hw_ram_ck       ), 
        .hw_ram_ckn         ( hw_ram_ckn      ), 
        .hw_ram_cke         ( hw_ram_cke      ), 
        .hw_ram_odt         ( hw_ram_odt      ),
        .hw_ram_ad          ( hw_ram_ad       ), 
        .hw_ram_dq          ( hw_ram_dq       ), 
        .hw_rzq_pin         ( pin_rzq_ref     ), 
        .hw_zio_pin         ( pin_zio_ref     ), 
        .clkout             ( ram_clkout      ), 
        .sys_clk            ( ram_clkout      ), 
        .rdy                ( ram_rdy         ), 
        .rd_data_pres       ( rd_data_pres    ),
        .max_ram_address    ( max_ram_address )
);
                      
ac97audio ac97audio_instance(   

        .sys_clk            ( ram_clkout      ),   
        .reset              ( ~reset          ), 
        .audio_in_data      ( data_to_ram     ), 
        .audio_out_data     ( data_from_ram   ),
        .ready              ( audio_rdy       ), 
        .audio_on           ( audio_on        ),
        .audio_reset_b      ( audio_reset_b   ), 
        .ac97_sdata_out     ( ac97_sdata_out  ), 
        .ac97_sdata_in      ( ac97_sdata_in   ),
        .ac97_synch         ( ac97_synch      ), 
        .ac97_bit_clock     ( ac97_bit_clock  ),
        .ac97_vol           ( jesus_juice     )
);

always@(posedge pb_read_strobe)
begin
    case(pb_port_id)
        8'h04:	pb_in_port <= {7'b0000000,fsm_wrt_req};
        8'h06:	pb_in_port <= lcd_nxt_state;
        default: pb_in_port <= 8'h00;
    endcase
end

always@(posedge pb_write_strobe)
begin
    case(pb_port_id)
        8'h00: lcd_enb <= pb_out_port[0];
        8'h01: lcd_rs <= pb_out_port[0];
        8'h02: lcd_rw <= pb_out_port[0];
        8'h03: lcd_data <= pb_out_port[3:0];
        8'h05: lcd_wrt_ack <= pb_out_port[0];
    endcase
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
