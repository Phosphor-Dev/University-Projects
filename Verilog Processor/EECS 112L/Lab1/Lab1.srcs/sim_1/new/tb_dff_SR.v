`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 07:50:34 PM
// Design Name: 
// Module Name: tb_dff_SR
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


module tb_dff_SR;
    reg r_clk;
    reg r_reset;
    reg r_d;
    reg r_set;
    wire w_q;

    dff_SR  tb_dff_SR(
        .clk(r_clk), 
        .reset(r_reset), 
        .d(r_d), 
        .set(r_set), 
        .q(w_q)
    );
    initial r_clk = 0;
    always #10 r_clk =~ r_clk;
    
    initial 
        begin
        r_reset = 0;
        r_d = 0;
        r_set = 0;
        #20;
        
        r_reset = 0;
        r_d = 1;
        r_set = 0;
        #20;
        
        r_reset = 1;
        r_d = 0;
        r_set = 0;
        #20;
        
        r_reset = 0;
        r_d = 1;
        r_set = 0;
        #20;
        
        r_reset = 0;
        r_d = 0;
        r_set = 0;
        #20;
        
        r_reset = 0;
        r_d = 0;
        r_set = 1;
        #20;
    end
      
endmodule
