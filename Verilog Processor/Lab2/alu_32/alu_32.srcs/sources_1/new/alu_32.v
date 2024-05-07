`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/30/2022 06:11:50 PM
// Design Name: 
// Module Name: alu_32
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


module alu_32(A_in, B_in , ALU_Sel , ALU_Out , Carry_Out , Zero , Overflow);
    // I/O Definition
    input [31:0] A_in;
    input [31:0] B_in;
    input [3:0] ALU_Sel;
    output [31:0] ALU_Out;
    output Carry_Out;
    output Zero;
    output Overflow;
    
    reg [31:0] out;
    reg carry;
    reg zero;
    reg over;
    
    
    // Behavior
    assign ALU_Out = out;
    assign Carry_Out = carry;
    assign Zero = zero;
    assign Overflow = over;
    always@(A_in or B_in or ALU_Sel)
        begin
            
            zero = 0;
            carry = 0;
            over = 0;
            
            case (ALU_Sel)
                4'b0000: begin // AND
                    out = A_in & B_in;
                    end
                
                4'b0001: begin // OR
                    out = $signed(A_in) | $signed(A_in);
                    end
                    
                4'b0010: begin // Add
                    {carry,out} = $signed(A_in) + $signed(A_in);
                    if (carry == 1'b1) begin // overflow
                        over = 1'b1;
                        end
                    
                    if ((out < 0) && (A_in > 0)&& (B_in > 0)) begin //positive to negative
                        over = 1;
                        end
                        
                    if ((out > 0) && (A_in < 0) && (B_in < 0)) begin //negative to positive
                        over = 1;
                        end
                    
                    end
                
                4'b0110: begin // Subtract
                    out = $signed(A_in) - $signed(B_in);
                    if ((out < 0) && (A_in > 0)&& (B_in > 0)) begin //positive to negative
                        over = 1;
                        end
                    
                    if ((out > 0) && (A_in < 0) && (B_in < 0)) begin //negative to positive
                        over = 1;
                        end
                    end
                
                4'b0111: begin // Set Less Than
                    if ($signed(A_in) < $signed(B_in)) begin
                        out = 32'b00000000000000000000000000000001;
                        end
                    else begin
                        out = 32'b00000000000000000000000000000000;
                        end
                    end
                
                4'b1100: begin // NOR
                    out = ~(A_in | B_in);
                    end
                
                4'b1111: begin // Equal Comparison;
                    if (A_in == B_in) begin
                        out = 32'b00000000000000000000000000000001;
                        end
                    else begin
                        out = 32'b00000000000000000000000000000000;
                        end
                    end
            endcase
            
            if (out == 32'h00000000) begin
                zero = 1'b1;
                end

        end
endmodule
