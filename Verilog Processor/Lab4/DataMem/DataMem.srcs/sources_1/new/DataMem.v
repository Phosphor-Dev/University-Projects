`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/28/2022 02:48:09 PM
// Design Name: 
// Module Name: DataMem
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


module DataMem (MemRead , MemWrite , addr , write_data , read_data);
//I/O Ports
    input MemRead;
    input MemWrite;
    input [8:0]addr;
    input [31:0]write_data;
    output wire [31:0]read_data;
    
    reg [31:0]data [127:0];
    reg [31:0]out;
    assign read_data = out;
//Behavior
    initial begin
        if (MemRead == 1'b1) begin
            out = data[addr[8:2]];
        end
    
    end
    
    initial begin
        if (MemWrite == 1'b1) begin
            data[addr[8:2]] = write_data;
        end
    
    end
endmodule
