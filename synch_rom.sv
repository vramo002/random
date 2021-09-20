`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/19/2021 05:53:57 PM
// Design Name: 
// Module Name: synch_rom
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


module synch_rom #(parameter FileName = "rom_1.mem")(
    input logic clk,
    input logic [7:0] addr,
    output logic [7:0] data
    );
    
     // signal declaration
    (*rom_style = "block" *)logic [7:0] rom [0:255];
    
    initial
        $readmemh(FileName, rom);
        
    always_ff @(posedge clk)
        data <= rom[addr];
        
endmodule
