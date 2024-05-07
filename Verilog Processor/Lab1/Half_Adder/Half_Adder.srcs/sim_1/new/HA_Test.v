`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 01:20:19 PM
// Design Name: 
// Module Name: HA_Test
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


module HA_Test();

    reg A_tb = 0;
    reg B_tb = 0;
    wire Sum_tb;
    wire Cout_tb;
    
    HA instant
        (
            .A(A_tb),
            .B(B_tb),
            .Sum(Sum_tb),
            .Cout(Cout_tb)
        );
    initial
        begin
            A_tb = 1'b0;
            B_tb = 1'b0;
            #10;
            
            A_tb = 1'b0;
            B_tb = 1'b1;
            #10;
            
            A_tb = 1'b1;
            B_tb = 1'b0;
            #10;
            
            A_tb = 1'b1;
            B_tb = 1'b1;
            #10;
    end
endmodule
