`timescale 1ns / 1ps

module test_fsm(
    input clk, 
    input reset, 
    input ram_it_hard, 
    input data_present_bro,
    input audio_rdy,
    input record, 
    input play,
    input[25:0] addr_start, 
    input[25:0] addr_end,
    output reg write_enb, 
    output reg read_req, 
    output reg read_ack,
    output reg[25:0] addr,
    output reg[7:0] leds
    );

    // state registers
    reg[1:0] wr_state;
    reg[1:0] rd_state;

    // write fsm state encoding 
    parameter write_set =           2'b00;
    parameter write =               2'b01;
    parameter write_disable =       2'b10;
    
    // read fsm state encoding
    parameter read_set =            2'b00;
    parameter read_request =        2'b01;
    parameter read_data =           2'b10;
    

    // function
    always@ (*) begin
        if (reset) begin
        
            wr_state <= write_set;
            rd_state <= read_set;
            write_enb <= 1'b0; 
            read_req <= 1'b0; 
            read_ack <= 1'b0;

        end else if (ram_it_hard) begin   
        
            if (record && !play) begin
            
                read_req <= 1'b0;
                read_ack <= 1'b0;
            
                case (wr_state)
                
                    write_set: begin
                        addr <= addr_start;
                        wr_state <= write;
                    end
                    
                    write: begin
                        if (audio_rdy && (addr < addr_end)) begin
                            write_enb <= 1'b1;
                            addr <= addr + 1'b1;
                            leds <= addr[7:0];
                            wr_state <= write_disable;
                        end
                    end
                    
                    write_disable: begin
                        write_enb <= 1'b0;
                        wr_state <= write;
                    end
                    
                endcase  
                
            end else if (play && !record) begin
                
                write_enb <= 1'b0;
                
                case (rd_state)
                
                    read_set: begin
                        addr <= addr_start;
                        rd_state <= read_request;
                    end
                
                    read_request: begin
                        read_ack <= 1'b0;
                        if (audio_rdy && (addr < addr_end)) begin
                            read_req <= 1'b1;
                            rd_state <= read_data;
                        end 
                    end
                    
                    read_data: begin
                        read_req <= 1'b0;
                        if (data_present_bro) begin
                            read_ack <= 1'b1;
                            addr <= addr + 1'b1;
                            leds <= addr[7:0];
                            rd_state <= read_request;
                        end
                    end
                    
                endcase 
                
            end else begin
                wr_state <= write_set;
                rd_state <= read_set;
                write_enb <= 1'b0; 
                read_req <= 1'b0; 
                read_ack <= 1'b0;
            end
     
        end
    end
    
endmodule
