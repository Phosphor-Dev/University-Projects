`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 09:39:37 PM
// Design Name: 
// Module Name: tb_dff_PC
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


module tb_dff_PC;
    reg r_clk;
    reg r_clear;
    reg r_d;
    reg r_preset;
    wire w_q;

    dff_PC tb_dff_PC(
        .clk(r_clk), 
        .clear(r_clear), 
        .d(r_d), 
        .preset(r_preset), 
        .q(w_q)
    );
    initial r_clk = 0;
    always #10 r_clk =~ r_clk;
    
    initial 
        begin
        r_clear = 0;
        r_d = 0;
        r_preset = 0;
        #20;
        
        r_clear = 0;
        r_d = 1;
        r_preset = 0;
        #20;
        
        r_clear = 1;
        r_d = 0;
        r_preset = 0;
        #20;
        
        r_clear = 0;
        r_d = 1;
        r_preset = 0;
        #20;
        
        r_clear = 0;
        r_d = 0;
        r_preset = 0;
        #20;
        
        r_clear = 0;
        r_d = 0;
        r_preset = 1;
        #20;
    end
      
endmodule
