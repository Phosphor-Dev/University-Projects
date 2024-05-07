`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: MUX21
// 
//////////////////////////////////////////////////////////////////////////////////

module MUX21 (
        D1 , D2 , S , Y
);
 
    input  S;
    input  [31:0]D1;
    input  [31:0]D2;
    
    output [31:0]Y;
    
    assign Y = (~S & D1) | (S & D2);
 

endmodule 

