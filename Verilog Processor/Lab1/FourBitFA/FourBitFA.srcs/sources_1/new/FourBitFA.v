`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 07:21:15 PM
// Design Name: 
// Module Name: FourBitFA
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


module FourBitFA(
    A,
    B,
    Cin,
    Sum,
    Cout
    );
    
    input [3:0] A;
    input [3:0] B;
    input Cin;
    output [3:0] Sum;
    output Cout;
    
    wire c1, c2, c3;
    //FA fa1(A[0], B[0], Cin, Sum[0], c1);
    //FA fa1(A[1], B[1], c1, Sum[1], c2);
    //FA fa2(A[2], B[2], c2, Sum[2], c3);
    //FA fa3(A[3], B[3], c3, Sum[3], Cout);
    
    assign Sum[0] = A[0] ^ B[0] ^ Cin;
    assign c1 = (A[0] & B[0]) | ((A[0] ^ B[0]) & Cin);
    
    assign Sum[1] = A[1] ^ B[1] ^ c1;
    assign c2 = (A[1] & B[1]) | ((A[1] ^ B[1]) & c1);
    
    assign Sum[2] = A[2] ^ B[2] ^ c2;
    assign c3 = (A[2] & B[2]) | ((A[2] ^ B[2]) & c2);
    
    assign Sum[3] = A[3] ^ B[3] ^ c3;
    assign Cout = (A[3] & B[3]) | ((A[3] ^ B[3]) & c3);
    
endmodule