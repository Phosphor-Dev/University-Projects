`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 08:39:25 PM
// Design Name: 
// Module Name: FourOneMUX_Test
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


module FourOneMUX_Test();
    reg S_tb = 0;
    reg D1_tb = 0;
    reg D2_tb = 0;
    reg D3_tb = 0;
    reg D4_tb = 0;
    wire Y_tb;
    
    FourOneMUX instant
        (
        .S(S_tb),
        .D1(D1_tb),
        .D2(D2_tb),
        .D3(D3_tb),
        .D4(D4_tb),
        .Y(Y_tb)
        );
    
    initial begin
    
    S_tb = 2'b00;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    #20;
    
    S_tb = 2'b01;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    #20;
    
    S_tb = 2'b10;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    #20;
    
    S_tb = 2'b11;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    D1_tb = 1'b0;
    D2_tb = 1'b1;
    #20;
    
    end


endmodule
