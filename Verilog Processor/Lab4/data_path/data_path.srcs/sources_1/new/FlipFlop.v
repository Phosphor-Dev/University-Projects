`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: FlipFlop
//////////////////////////////////////////////////////////////////////////////////

// Module definition
module FlipFlop(
   input  clk , reset,
   input  [7:0] d,
   output reg[7:0] q = 0
   );
   
always @(posedge clk) begin
    if(reset == 1'b1)
        q = 8'b00000000;
    else
        q = d;
    end

endmodule 




