`timescale 1ns / 1ps

module InstMem_tb();

    reg [7:0]addr;
    wire [32:0]instruction;
    
    InstMem instant(
        .addr(addr),
        .instruction(instruction)
    );
    
    initial begin
        addr = 8'b00000000;
        #20;
        
        addr = 8'b00000100;
        #20;
        
        addr = 8'b00011000;
        #20;
    end
    
    
    
endmodule
