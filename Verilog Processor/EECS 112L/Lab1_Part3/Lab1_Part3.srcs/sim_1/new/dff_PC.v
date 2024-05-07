`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 09:39:06 PM
// Design Name: 
// Module Name: dff_PC
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


module dff_PC(
    clk,
    d,
    preset,
    clear,
    q
    );
    
    
    input clk;
    input d;
    input preset;
    input clear;
    output q;
    
    reg temp;
    assign q = temp;
    
    always @(posedge preset or posedge clear or posedge clk)
    begin
        if (clear == 1)
            temp = 0;  
        else if(preset == 1)
            temp <= 1;
        else
            temp <= d;      
    end  
endmodule
