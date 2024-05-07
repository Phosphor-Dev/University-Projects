`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 07:22:06 PM
// Design Name: 
// Module Name: FourBitFA_Test
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


module FourBitFA_Test();
    reg [3:0] A_tb = 0;
    reg [3:0] B_tb = 0;
    reg Cin_tb = 0;
    wire [3:0] Sum_tb;
    wire Cout_tb;
    
    FourBitFA instant  
        (
         .A(A_tb), 
         .B(B_tb), 
         .Cin(Cin_tb), 
         .Sum(Sum_tb), 
         .Cout(Cout_tb)
        );

    initial 
        begin        
            A_tb     = 4'b0110;
            B_tb     = 4'b0100;
            Cin_tb   = 4'b0;
            #20;
            
            A_tb     = 4'b1000;
            B_tb     = 4'b1001;
            Cin_tb   = 4'b1;
            #20;
            
            A_tb     = 4'd1110;
            B_tb     = 4'd0010;
            Cin_tb   = 4'b0;
            #20;
            
            A_tb     = 4'd1010;
            B_tb     = 4'd1011;
            Cin_tb   = 4'b0;
            #20;
        
   end
endmodule

