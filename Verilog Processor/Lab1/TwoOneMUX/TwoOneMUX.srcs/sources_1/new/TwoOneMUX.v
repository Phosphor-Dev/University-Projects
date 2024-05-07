`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 08:17:23 PM
// Design Name: 
// Module Name: TwoOneMUX
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


module TwoOneMUX(
    input S,
    input D1,
    input D2,
    output Y);
    
    assign Y = (~S & D1) | (S & D2);assign Y = (~S & D1) | (S & D2);
    
endmodule
