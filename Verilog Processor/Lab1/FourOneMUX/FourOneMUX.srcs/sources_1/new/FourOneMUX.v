`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 08:39:04 PM
// Design Name: 
// Module Name: FourOneMUX
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


module FourOneMUX(
    input [1:0]S,
    input D1,
    input D2,
    input D3,
    input D4,
    output Y);
    
    assign Y = (~S[0] & ~S[1] & D1) | (~S[0] & S[1] & D2) | (S[0] & ~S[1] & D3) | (S[0] & S[1] & D4);
endmodule
