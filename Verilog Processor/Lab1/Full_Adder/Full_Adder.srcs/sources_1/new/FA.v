`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 01:47:03 PM
// Design Name: 
// Module Name: FA
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

module FA(
    A,
    B,
    Cin,
    Sum,
    Cout
    );
    
    input A;
    input B;
    input Cin;
    output Sum;
    output Cout;
    
    assign Sum = A ^ B ^ Cin;
    assign Cout = (A & B) | ((A ^ B) & Cin);
    
endmodule
