`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 07:52:39 PM
// Design Name: 
// Module Name: dff_SR
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


module dff_SR(
    clk,
    d,
    set,
    reset,
    q
    );
    
    
    input clk;
    input d;
    input set;
    input reset;
    output reg q;
    
    always @(posedge(clk))
    begin
        if(clk == 1) 
        begin
            if (reset == 1)
                q = 0;  
            else if(set == 1)
                q = 1;
            else
                q = d;
        end      
    end  
endmodule