`timescale 1ns / 1ps

module EX_pipe_stage(
    input [31:0] id_ex_instr,
    input [31:0] reg1, reg2,
    input [31:0] id_ex_imm_value,
    input [31:0] ex_mem_alu_result,
    input [31:0] mem_wb_write_back_result,
    input id_ex_alu_src,
    input [1:0] id_ex_alu_op,
    input [1:0] Forward_A, Forward_B,
    output [31:0] alu_in2_out,
    output [31:0] alu_result
    );
    //REGS and WIRES
    //alu_result
    
    //alu_in2_out
    
    //ASSIGNS
    wire [31:0]id_ex_reg1_mux_wire;
    wire [31:0]id_ex_reg2_mux_wire;
    wire [31:0]alu_in2_wire;
    wire [3:0]ALU_Control_wire;
    
    wire zero_wire;
    assign zero_wire = 1'b0;
    mux4 #(.mux_width(32)) id_ex_reg1_mux
    (   .a(reg1),
        .b(mem_wb_write_back_result),
        .c(ex_mem_alu_result),
        .d(1'b0),//idk what to put here
        .sel(Forward_A),
        .y(id_ex_reg1_mux_wire));
    
    mux4 #(.mux_width(32)) id_ex_reg2_mux
    (   .a(reg2),
        .b(mem_wb_write_back_result),
        .c(ex_mem_alu_result),
        .d(1'b0),//idk what to put here
        .sel(Forward_B),
        .y(id_ex_reg2_mux_wire));
        
    
    mux2 #(.mux_width(32)) id_ex_imm_value_mux
    (   .a(id_ex_reg2_mux_wire),
        .b(id_ex_imm_value),
        .sel(id_ex_alu_src),
        .y(alu_in2_wire));
    
    ALUControl ALUControl_inst(
        .ALUOp(id_ex_alu_op), 
        .Function(id_ex_instr[5:0]),
        .ALU_Control(ALU_Control_wire)
    );
    
    ALU ALU_inst (
        .a(id_ex_reg1_mux_wire),  
        .b(alu_in2_wire), 
        .alu_control(ALU_Control_wire),
        .zero(zero_wire), 
        .alu_result(alu_result)
    );
        
       
endmodule
