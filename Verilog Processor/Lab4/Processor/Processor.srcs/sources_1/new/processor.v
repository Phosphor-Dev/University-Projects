`timescale 1ns / 1ps

module processor
(
input clk , reset ,
output [31:0] Result
);

wire [6:0]Funct7;
wire [2:0]Funct3;
wire [6:0]opcode;
wire [1:0]ALUOp;
wire RegWrite;
wire ALUSrc;
wire MemRead;
wire MemWrite;
wire MemtoReg;
wire [3:0]Operation;

wire [31:0]tResult;
assign Result = tResult;



// Define the processor modules behavior
data_path data_pathInst(
    .clk(clk),
    .reset(reset),
    .reg_write(RegWrite),
    .mem2reg(MemtoReg),
    .alu_src(ALUSrc),
    .mem_write(MemWrite),
    .mem_read(MemRead),
    .alu_cc(Operation),
    .opcode(opcode),
    .funct7(Funct7),
    .funct3(Funct3),
    .alu_result(tResult)
    );
    
controller controllerInst(
    .Opcode(opcode),
    .ALUOp(ALUOp),
    .RegWrite(RegWrite),
    .ALUSrc(ALUSrc),
    .MemRead(MemRead) ,
    .MemWrite(MemWrite),
    .MemtoReg(MemtoReg)
);

ALUController ALUControllerInst(
    .Funct7(Funct7),
    .Funct3(Funct3),
    .ALUOp(ALUOp),
    .Operation(Operation)
);


endmodule // processor
