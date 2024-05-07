`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/30/2022 07:03:54 PM
// Design Name: 
// Module Name: alu_32_tb
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


module alu_32_tb();
    //INPUTS
    reg [31:0] A_in = 0;
    reg [31:0] B_in = 0;
    reg [3:0] ALU_Sel = 0;
    
    //OUTPUTS
    wire [31:0] ALU_Out;
    wire Carry_Out;
    wire Zero;
    wire Overflow;
    
    alu_32 instant(
        .A_in(A_in),
        .B_in(B_in),
        .ALU_Sel(ALU_Sel),
        .ALU_Out(ALU_Out),
        .Carry_Out(Carry_Out),
        .Zero(Zero),
        .Overflow(Overflow)
    );
    
    initial
        begin
            A_in = 32'h086a0c31;
            B_in = 32'hd785f148;
            ALU_Sel = 4'b0000;
            #20;
            
            A_in = 32'h086a0c31;
            B_in = 32'h10073fd4;
            ALU_Sel = 4'b0001;
            #20;
            
            A_in = 32'ha86a0c31;
            B_in = 32'h90073fd4;
            ALU_Sel = 4'b0010;
            #20;
            
            A_in = 32'ha86a0c31;
            B_in = 32'h90073fd4;
            ALU_Sel = 4'b0110;
            #20;
            
            A_in = 32'ha86a0c31;
            B_in = 32'h90073fd4;
            ALU_Sel = 4'b0111;
            #20;
            
            A_in = 32'ha86a0c31;
            B_in = 32'h90073fd4;
            ALU_Sel = 4'b1100;
            #20;
            
            A_in = 32'ha86a0c31;
            B_in = 32'ha86a0c31;
            ALU_Sel = 4'b1111;
            #20;
            
            A_in = 32'ha86a0c31;
            B_in = 32'h10073fd4;
            ALU_Sel = 4'b1111;
            #20;
            
            A_in = 32'h00000000;
            B_in = 32'h00000000;
            ALU_Sel = 4'b0000;
            #60;
            
            //SELF TEST
            A_in = 32'b11111111111111111111111111111111; //ADD POS OVERFLOW
            B_in = 32'b11111111111111111111111111111111;
            ALU_Sel = 4'b0010;
            #20;
            
            A_in = -32'b11111111111111111111111111111111; //ADD NEG OVERFLOW
            B_in = -32'b11111111111111111111111111111111;
            ALU_Sel = 4'b010;
            #20;
            
            A_in = 32'b11111111111111111111111111111111; //SUB POS OVERFLOW
            B_in = -32'b11111111111111111111111111111111;
            ALU_Sel = 4'b0110;
            #20;
            
            A_in = -32'b11111111111111111111111111111111; //SUB NEG OVERFLOW
            B_in = 32'b11111111111111111111111111111111;
            ALU_Sel = 4'b0110;
            #20;
            
            A_in = 32'h00000000;
            B_in = 32'h00000000;
            ALU_Sel = 4'b0000;
            #60;
        end
    
endmodule
