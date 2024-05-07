`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 05:40:49 PM
// Design Name: 
// Module Name: FourBFA_Test
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


module FourBFA_Test();
    reg [3:0] A;
    reg [3:0] B;
    reg Cin;
    wire [3:0] Sum;
    wire Cout;
    
    FourBFA  uut   
        (
         .A(A), 
         .B(B), 
         .Cin(Cin), 
         .Sum(Sum), 
         .Cout(Cout)
        );

    initial begin
        A    = 4'b0000;
        B    = 4'b0000;
        Cin  = 4'b0;
        #100;
        
        A    = 4'b0110;
        B    = 4'b0100;
        Cin  = 4'b0;
        #20;
        
        A    = 4'b1000;
        B    = 4'b1001;
        Cin  = 4'b1;
        #20;
        
        A    = 4'd1110;
        B    = 4'd0010;
        Cin  = 4'b0;
        #20;
        
        A    = 4'd1010;
        B    = 4'd1011;
        Cin  = 4'b0;
        #20;
        
   end
endmodule
