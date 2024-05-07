`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 03:29:43 PM
// Design Name: 
// Module Name: tb_alu
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


module tb_alu;
    reg [3:0]r_A = 0;
    reg [3:0]r_B = 0;
    reg [3:0]r_ALU_Sel;
    wire [3:0]w_ALU_Out ;
    wire w_CarryOut ;   
    
    reg [4:0]i, j = 0;
    
    alu_fixed alu_fixed_inst
        (
        .A(r_A),
        .B(r_B),
        .ALU_Sel(r_ALU_Sel),
        .ALU_Out(w_ALU_Out),
        .CarryOut(w_CarryOut)
        );
        
    initial
        begin
            //Add
            r_A = 4'b0000;
            r_B = 4'b0000;
            r_ALU_Sel = 4'b0000;
            for (i = 0; i < 16; i = i + 1) begin
                for (j = 0; j < 16; j = j + 1) begin
                    #1;
                    r_B <= r_B + 4'b0001;
                end
                r_A <= r_A + 4'b0001;
            end
        end
endmodule

