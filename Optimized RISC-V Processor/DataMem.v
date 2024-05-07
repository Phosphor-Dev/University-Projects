`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
/// data memory
//////////////////////////////////////////////////////////////////////////////////

module DataMem(MemRead, MemWrite, addr, write_data, read_data);

// Define I/O ports
    input MemRead;
    input MemWrite;
    input [8:0]addr;
    input [31:0]write_data;
    output wire [31:0]read_data;
    
    reg [31:0]data [127:0];
    reg [31:0]out;
    assign read_data = out;
// Describe DataMem behavior 
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
     
