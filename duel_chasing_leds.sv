`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/20/2021 08:51:10 PM
// Design Name: 
// Module Name: duel_chasing_leds
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module duel_chasing_leds(
        input logic [7:0] speed, 
        input logic stop,
        input logic reset, 
        input logic clk,
        output logic [15:0] leds,
        output logic [6:0] sseg,
        output logic [7:0] an
    );
    
    
    logic m_tick;
    logic [31:0] m_count;
    int i = 0;
    logic [11:0] disp;
    
    mod_m_counter #(.M(1_000_000)) ticker (
                    .clk(clk),
                    .reset(reset),  
                    .q(),
                    .max_tick(m_tick)
    );
    
    binary_counter #(.N(32)) m_tick_counter(
        .q(m_count),
        .en(m_tick),
        .max_tick(),
        .*
    ); 
    
    always_comb
    begin 
        if (speed < 31)
            i = 5;
        else if (speed < 63)
            i = 10;
        else if (speed < 95)
            i = 14;
        else if (speed < 127)
            i = 18;
        else if (speed < 159)
            i = 23;
        else if (speed < 191)
            i = 30;
        else if (speed < 223)
            i = 36;
        else if (speed < 254)
            i = 43;
        else
            i = 50;
    end
    
    typedef enum {one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen} state_type;
    
    // signal declarations
    state_type state_reg, state_next;
    
    // state register
    always_ff @(posedge clk, posedge reset)
        if(reset)
        begin
            state_reg <= one;
        end
        else
        begin
            state_reg <= state_next;
        end
            
    always_comb
    begin
        case(state_reg)
            one:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b1000000000000001;
                    //m_count = 0;
                    state_next = two;
                end
                else
                    state_next = one;
                /*else if(m_count%i == 0 && !stop)
                begin 
                    state_next = one;
                end
                else if(stop)
                    state_next = one;*/
             two:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b0100000000000010;
                    //m_count = 0;
                    state_next = three;
                end
                else
                    state_next = two;
                /*else if(m_count%i != 0 && !stop)
                begin
                    state_next = two;
                end
                else if(stop)
                    state_next = two;*/
              three:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b0010000000000100;
                    //m_count = 0;
                    state_next = four;
                end
                else
                    state_next = three;
                /*else if(m_count%i != 0 && !stop)
                begin
                    state_next = three;
                end
                else if(stop)
                    state_next = three;*/
              four:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b0001000000001000;
                    //m_count = 0;
                    state_next = five;
                end
                else
                    state_next = four;
                /*else if(m_count%i != 0 && !stop)
                begin
                    state_next = four;
                end*/
              five:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b0000100000010000;
                    //m_count = 0;
                    state_next = six;
                end
                else
                begin
                    state_next = five;
                end
              six:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b0000010000100000;
                    //m_count = 0;
                    state_next = seven;
                end
                else
                begin
                    state_next = six;
                end
              seven:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    //leds[15:0] = 16'b0000001001000000;
                    //m_count = 0;
                    state_next = eight;
                end
                else
                begin
                    state_next = seven;
                end
              eight:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = nine;
                end
                else
                begin
                    state_next = eight;
                end
              nine:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = ten;
                end
                else
                begin
                    state_next = nine;
                end
              ten:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = eleven;
                end
                else
                begin
                    state_next = ten;
                end
                //////////////////////
              eleven:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = twelve;
                end
                else
                begin
                    state_next = eleven;
                end
              twelve:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = thirteen;
                end
                else
                begin
                    state_next = twelve;
                end
              thirteen:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = fourteen;
                end
                else 
                begin
                    state_next = thirteen;
                end
              fourteen:
                if(m_count%i == 0 && m_tick && !stop)
                begin
                    state_next = one;
                end
                else
                begin
                    state_next = fourteen;
                end
              /*fifteen:
                if(m_count%i == 0 && m_tick)
                begin
                    state_next = sixteen;
                end
                else if(m_count%i != 0)
                begin
                    state_next = fifteen;
                end
              sixteen:
                if(m_count%i == 0 && m_tick)
                begin
                    state_next = one;
                end
                else if(m_count%i != 0)
                begin
                    state_next = sixteen;
                end*/
              
              default:
                state_next = one;
        endcase
    end
    
    
    always_comb
    begin 
        if(state_reg == one)
            leds[15:0] = 16'b1000000000000001;
        else if(state_reg == two)
            leds[15:0] = 16'b0100000000000010;
        else if(state_reg == three)
            leds[15:0] = 16'b0010000000000100;
        else if(state_reg == four)
            leds[15:0] = 16'b0001000000001000;
        else if(state_reg == five)
            leds[15:0] = 16'b0000100000010000;
        else if(state_reg == six)
            leds[15:0] = 16'b0000010000100000;
        else if(state_reg == seven)
            leds[15:0] = 16'b0000001001000000;
        else if(state_reg == eight)
            leds[15:0] = 16'b0000000110000000;
        else if(state_reg == nine)
            leds[15:0] = 16'b0000001001000000;
        else if(state_reg == ten)
            leds[15:0] = 16'b0000010000100000;
        else if(state_reg == eleven)
            leds[15:0] = 16'b0000100000010000;
        else if(state_reg == twelve)
            leds[15:0] = 16'b0001000000001000;
        else if(state_reg == thirteen)
            leds[15:0] = 16'b0010000000000100;
        else if(state_reg == fourteen)
            leds[15:0] = 16'b0100000000000010;
    end
    
    bin2bcd in (
        .bin(speed),
        .bcd(disp)
    );
    
    time_mux_disp dispa (
        .in0({1'b1 ,disp[3:0], 1'b1}),
        .in1({1'b1 ,disp[7:4], 1'b1}),
        .in2({1'b1 ,disp[11:8], 1'b1}),
        .in3(),
        .in4(),
        .in5(),
        .in6(),
        .in7(),
        .dp(),
        .*
    );
endmodule
