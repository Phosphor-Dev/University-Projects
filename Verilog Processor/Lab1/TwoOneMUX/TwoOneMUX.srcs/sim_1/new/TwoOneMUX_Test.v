`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 08:21:05 PM
// Design Name: 
// Module Name: TwoOneMUX_Test
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


module TwoOneMUX_Test();
    reg S_tb;
    reg D1_tb;
    reg D2_tb;
    wire Y_tb;
    
    TwoOneMUX instant
        (
        .S(S_tb),
        .D1(D1_tb),
        .D2(D2_tb),
        .Y(Y_tb)
        );
    
    initial begin
    
    S_tb = 1'b0;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    #20;
    
    S_tb = 1'b1;
    D1_tb = 1'b1;
    D2_tb = 1'b0;
    #20;
    
    end
endmodule
