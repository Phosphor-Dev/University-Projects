`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2022 11:30:29 PM
// Design Name: 
// Module Name: RegFile_tb
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


module RegFile_tb();
    reg clk;
    reg reset;
    reg rg_wrt_en;
    reg [4:0]rg_wrt_addr;
    reg [4:0]rg_rd_addr1;
    reg [4:0]rg_rd_addr2;
    reg [31:0]rg_wrt_data;
    wire [31:0]rg_rd_data1;
    wire [31:0]rg_rd_data2;
    
    RegFile instant(
        .clk(clk), 
        .reset(reset), 
        .rg_wrt_en(rg_wrt_en),
        .rg_wrt_addr(rg_wrt_addr),
        .rg_rd_addr1(rg_rd_addr1),
        .rg_rd_addr2(rg_rd_addr2),
        .rg_wrt_data(rg_wrt_data),
        .rg_rd_data1(rg_rd_data1),
        .rg_rd_data2(rg_rd_data2)
    );

always #20 clk = ~clk;

initial begin
    reset = 1;
    #100 
    reset = 0;
    rg_wrt_en = 0;
    rg_wrt_addr = 0;
    rg_rd_addr1 = 0;
    rg_rd_addr2 = 0;
    rg_wrt_data = 0;
    #100;
    rg_wrt_en = 1;
    rg_wrt_addr = 0;
    rg_rd_addr1 = 1;
    rg_rd_addr2 = 2;
    rg_wrt_data = 3;
    #100;
    rg_wrt_en = 0;
    rg_wrt_addr = 0;
    rg_rd_addr1 = 0;
    rg_rd_addr2 = 0;
    rg_wrt_data = 0;
    
end
endmodule
