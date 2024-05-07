`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2022 04:39:52 PM
// Design Name: 
// Module Name: FlipFlop
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


module FlipFlop(clk, reset, d, q);

// I/O
input clk;
input reset;
input [7:0]d;
output reg [7:0]q = 0;

//Behavior

always @(posedge clk) begin
    if(reset == 1'b1)
        q = 8'b00000000;
    else
        q = d;
    end
endmodule
