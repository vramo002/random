`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/06/2021 09:00:28 PM
// Design Name: 
// Module Name: square_wave_generator
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


module square_wave_generator(
        input logic clk, reset,
        input logic [3:0] m,
        input logic [3:0] n,
        //output logic [3:0] r,
        //output logic [3:0] a,
        output logic square_wave
    );
    
    //signal decaration
    logic [3:0] r_next, r_reg;
    logic [3:0] a_next, a_reg;
    logic [3:0] sw_next, sw_reg;
    logic [3:0] r_r_next;//, r_r_reg;
    logic [3:0] a_a_next;
    //body
    //
    always_ff @(posedge clk, posedge reset)
    begin 
        if (reset)
        begin
            r_reg <= 0;
            a_reg <= 0;
            sw_reg <= 0;
        end
        else
        begin
            r_reg <= r_next;
            a_reg <= a_next;
            sw_reg <= sw_next;
        end
    end
    
    assign r_r_next = r_reg + 1;
    
    /*always_ff @(*)
    begin 
        r_r_next <= r_reg + 1;
    end*/
    
    always_comb
    begin
        r_next = r_r_next;
        a_a_next = a_reg;
        if(r_reg == 10-1)
        begin
            a_a_next = a_reg + 1;
            r_next = 0;
        end
    end
    
    always_comb//_ff @(*)
    begin 
        //r_next <= r_r_next;//r_reg + 1;
        a_next = a_a_next;//a_reg;
        sw_next = sw_reg;
        /*if(r_reg == 5 - 1)
        begin
            a_next <= a_reg + 1;
            r_next <= 0;
        end*/
        if(sw_reg == 0 && a_reg == m && m != 0)
        begin
            sw_next = 1;
            a_next = 0;
        end
        if(sw_reg == 1 && a_reg == n && n != 0)
        begin
            sw_next = 0;
            a_next = 0;
        end
        /*if(n == 0 && m == 0)
        begin
            sw_next = 0;
            a_next = 0;
        end*/
    end
    
    /*always_ff @(*)
    begin 
        a_next <= a_reg;
        sw_next <= sw_reg;
        
        if(sw_reg == 0 && a_reg == m)
        begin
            sw_next <= 1;
            a_next <= 0;
        end
        if(sw_reg == 1 && a_reg == n)
        begin
            sw_next <= 0;
            a_next <= 0;
        end
    end*/
    
    
    //assign r = r_reg;
    //assign a = a_reg;
    assign square_wave = sw_reg;
    
endmodule
