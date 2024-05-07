`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 04:34:43 PM
// Design Name: 
// Module Name: FA_Test
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


module FA_Test();

    reg A_tb = 0;
    reg B_tb = 0;
    reg Cin_tb = 0;
    wire Sum_tb;
    wire Cout_tb;
    
    FA instant
        (
        .A(A_tb),
        .B(B_tb),
        .Cin(Cin_tb),
        .Sum(Sum_tb),
        .Cout(Cout_tb)
        );
        
    initial
        begin
            A_tb = 1'b0;
            B_tb = 1'b0;
            Cin_tb = 1'b0;
            #10;
            
            A_tb = 1'b0;
            B_tb = 1'b0;
            Cin_tb = 1'b1;
            #10;
            
            A_tb = 1'b0;
            B_tb = 1'b1;
            Cin_tb = 1'b0;
            #10;
            
            A_tb = 1'b0;
            B_tb = 1'b1;
            Cin_tb = 1'b1;
            #10;
            
            A_tb = 1'b1;
            B_tb = 1'b0;
            Cin_tb = 1'b0;
            #10;
            
            A_tb = 1'b1;
            B_tb = 1'b0;
            Cin_tb = 1'b1;
            #10;
            
            A_tb = 1'b1;
            B_tb = 1'b1;
            Cin_tb = 1'b0;
            #10;
            
            A_tb = 1'b1;
            B_tb = 1'b1;
            Cin_tb = 1'b1;
            #10;
            
        end    
endmodule
