`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2022 05:02:36 PM
// Design Name: 
// Module Name: FlipFlop_tb
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


module FlipFlop_tb();
    reg clk = 0;
    reg reset = 1;
    reg [7:0] d = 0;
    
    wire [7:0] q;
    
    FlipFlop instant(
        .clk(clk),
        .reset(reset),
        .d(d),
        .q(q)
    );
    
    always #20 clk = ~clk;
    
    initial begin
        #100 reset = 0;
        
        d = 8'b11110000;
        #10;
        d = 8'b00001111; 
        #10
        d = 8'b11110000;
        #20;
        d = 8'b00001111;
    end
endmodule
