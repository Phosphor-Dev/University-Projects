`timescale 1ns / 1ps

// Module definition
module ALUController (
ALUOp , Funct7 , Funct3 , Operation
);

// Define the input and output signals
input [1:0]ALUOp;
input [6:0]Funct7;
input [2:0]Funct3;
output wire[3:0]Operation;
reg tOperation;
assign Operation = tOperation;

// Define the ALUController modules behavior

always @(ALUOp or Funct7 or Funct3)
begin
    if (ALUOp == 2'b10) begin
        if ((Funct7 == 7'b0000000) && (Funct3 ==3'b111))
            tOperation = 4'b0000;
       
        if ((Funct7 == 7'b0000000) && (Funct3 ==3'b110))
            tOperation = 4'b0001;
        
        if ((Funct7 == 7'b0000000) && (Funct3 ==3'b100))
            tOperation = 4'b1100;
        
        if ((Funct7 == 7'b0000000) && (Funct3 ==3'b010))
            tOperation = 4'b0111;
        
        if ((Funct7 == 7'b0000000) && (Funct3 ==3'b000))
            tOperation = 4'b0010;
        
        if ((Funct7 == 7'b0100000) && (Funct3 ==3'b000))
            tOperation = 4'b0110;
    end
    
    
    
    if (ALUOp == 2'b00) begin
        if (Funct3 == 3'b111)
            tOperation = 4'b0000;
        if (Funct3 == 3'b110)
            tOperation = 4'b0001;
        if (Funct3 == 3'b100)
            tOperation = 4'b1100;
        if (Funct3 == 3'b010)
            tOperation = 4'b0111;
        if (Funct3 == 3'b000)
            tOperation = 4'b0010;    
    end
    
    if (ALUOp == 2'b01) begin
        if (Funct3 == 3'b010)
            tOperation = 4'b0010;
    end
end
endmodule // ALUController