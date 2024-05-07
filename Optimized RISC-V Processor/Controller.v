`timescale 1ns / 1ps



// Module definition
module controller (
Opcode ,
ALUSrc , MemtoReg , RegWrite , MemRead , MemWrite ,
ALUOp
);


// Define the input and output signals
input [6:0]Opcode;
output wire[1:0] ALUOp;
output reg RegWrite;
output reg ALUSrc;
output reg MemRead;
output reg MemWrite;
output reg MemtoReg;
reg tALUOp;
assign ALUOp = tALUOp;

// Define the Controller modules behavior

always @(Opcode)
begin
    case (Opcode)
        7'b0110011 : begin
            tALUOp = 2'b10;
            RegWrite = 1;
            ALUSrc = 0;
            MemRead = 0;
            MemWrite = 0;
            MemtoReg = 0;
            end
        

        7'b0010011 : begin
            tALUOp = 2'b00;
            RegWrite = 1;
            ALUSrc = 1;
            MemRead = 0;
            MemWrite = 0;
            MemtoReg = 0;
            end
        
        7'b0000011 : begin
            tALUOp = 2'b01;
            RegWrite = 1;
            ALUSrc = 1;
            MemRead = 1;
            MemWrite = 0;
            MemtoReg = 1; 
            end
        

        7'b0100011 : begin
            tALUOp = 2'b01;
            RegWrite = 0;
            ALUSrc = 1;
            MemRead = 0;
            MemWrite = 1;
            MemtoReg = 0;
            end  


    endcase
end

endmodule // Controller
