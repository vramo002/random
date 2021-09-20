`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/19/2021 05:28:56 PM
// Design Name: 
// Module Name: rom_base_temp_conv
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


module rom_base_temp_conv(
    input logic clk,
    input logic [7:0] tempinput,
    input logic tempformat,
    output logic [7:0] display
    );
    
    logic [7:0] Fdata, Cdata;
    
    //instantiate roms
    //CtoF.mem
    synch_rom #(.FileName("CtoF.mem")) rom1 (
                .clk(clk),
                .addr(tempinput),
                .data(Fdata)
    );
    
    //FtoC.mem
    synch_rom #(.FileName("FtoC.mem")) rom2 (
                .clk(clk),
                .addr(tempinput),
                .data(Cdata)
    );
    
    always_comb
    begin
        if(tempformat)
            display = Fdata;
        else
            display = Cdata;
    end
    
endmodule
