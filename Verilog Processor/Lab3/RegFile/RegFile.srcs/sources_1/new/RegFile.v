`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2022 07:26:45 PM
// Design Name: 
// Module Name: RegFile
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


module RegFile (
    clk, 
    reset, 
    rg_wrt_en,
    rg_wrt_addr,
    rg_rd_addr1,
    rg_rd_addr2,
    rg_wrt_data,
    rg_rd_data1,
    rg_rd_data2
    );
    
    // I/O
    input clk;
    input reset;
    input rg_wrt_en;
    input [4:0]rg_wrt_addr;
    input [4:0]rg_rd_addr1;
    input [4:0]rg_rd_addr2;
    input [31:0]rg_wrt_data;
    output [31:0]rg_rd_data1;
    output [31:0]rg_rd_data2;
    
    integer i;
    output reg [31:0]register[0:31];
    
    reg data1;
    reg data2;
    assign rg_rd_data1 = data1;
    assign rg_rd_data2 = data2;
    
    
     
    //Behavior
    /*always @ (rg_rd_addr1 or rg_rd_addr2 or reset or clk or rg_wrt_en or rg_wrt_addr or rg_wrt_data) begin
        if(rg_wrt_en == 1'b0) begin
            rg_rd_data1 = register[rg_rd_addr1];
            rg_rd_data2 = register[rg_rd_addr2];
        end
    end*/
    
    always @ (posedge clk) begin
        if (reset == 1'b1) begin
            for (i = 0; i < 32; i = i + 1)begin
                register[i] = 32'h00000000;
            end
        end

        else if (rg_wrt_en == 1'b1) begin
            if (reset == 1'b0) begin
                register[rg_wrt_addr] = rg_wrt_data;   
            end
        end
                
        data1 = register[rg_rd_addr1];
        data2 = register[rg_rd_addr2];
    end
    /*
    always @ (reset) begin
        if (reset == 1'b1) begin
            for (i = 0; i < 32; i = i + 1)begin
                register[i] = 32'h00000000;
            end
        end
    end*/
    
    
endmodule
