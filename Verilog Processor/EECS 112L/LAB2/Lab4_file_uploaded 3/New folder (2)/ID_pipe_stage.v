`timescale 1ns / 1ps


module ID_pipe_stage(
    input  clk, reset,
    input  [9:0] pc_plus4,
    input  [31:0] instr,
    input  mem_wb_reg_write,
    input  [4:0] mem_wb_write_reg_addr,
    input  [31:0] mem_wb_write_back_data,
    input  Data_Hazard,
    input  Control_Hazard,
    output [31:0] reg1, reg2,
    output [31:0] imm_value,
    output [9:0] branch_address,
    output [9:0] jump_address,
    output branch_taken,
    output [4:0] destination_reg, 
    output mem_to_reg,
    output [1:0] alu_op,
    output mem_read,  
    output mem_write,
    output alu_src,
    output reg_write,
    output jump
    );
    
    
    // Remember that we test if the branch is taken or not in the decode stage.

    //Regs and Wires
    //mem_to_reg, alu_op, mem_read, mem_write, alu_src, reg_write
    wire reg_dst_wire;
    wire branch_wire;

    //branch taken
    wire eq_test_wire;
    
    //reg1 and reg2
    wire [31:0]reg1_wire;
    wire [31:0]reg2_wire;
    //imm_value
    wire [31:0]imm_value_wire;
    
    
    //Assigns
    //mem_to_reg, alu_op, mem_read, mem_write, alu_src, reg_write
    wire mem_to_reg_wire;
    wire [1:0]alu_op_wire;
    wire mem_read_wire;
    wire mem_write_wire;
    wire alu_src_wire;
    wire reg_write_wire;
    
    control control_inst(
        .reset(reset),
        .opcode(instr[31:26]),
        .reg_dst(reg_dst_wire), 
        .mem_to_reg(mem_to_reg_wire), 
        .alu_op(alu_op_wire),  
        .mem_read(mem_read_wire),
        .mem_write(mem_write_wire),
        .alu_src(alu_src_wire),
        .reg_write(reg_write_wire),
        .branch(branch_wire),
        .jump(jump)
    );
    
    mux2 #(.mux_width(1)) mem_to_reg_mux
    (   .a(mem_to_reg_wire),
        .b(1'b0),
        .sel((!Data_Hazard & Control_Hazard)),
        .y(mem_to_reg));
    
    mux2 #(.mux_width(2)) alu_op_mux
    (   .a(alu_op_wire),
        .b(2'b00),
        .sel((!Data_Hazard & Control_Hazard)),
        .y(alu_op));
        
    mux2 #(.mux_width(1)) mem_read_mux
    (   .a(mem_read_wire),
        .b(1'b0),
        .sel((!Data_Hazard & Control_Hazard)),
        .y(mem_read));
        
    mux2 #(.mux_width(1)) mem_write_mux
    (   .a(mem_write_wire),
        .b(1'b0),
        .sel((!Data_Hazard & Control_Hazard)),
        .y(mem_write));
        
    mux2 #(.mux_width(1)) alu_src_mux
    (   .a(alu_src_wire),
        .b(1'b0),
        .sel((!Data_Hazard & Control_Hazard)),
        .y(alu_src));
        
    mux2 #(.mux_width(1)) reg_write_mux
    (   .a(reg_write_wire),
        .b(1'b1),
        .sel((!Data_Hazard & Control_Hazard)),
        .y(reg_write));
    
    //jump_address
    assign jump_address = instr[25:0] << 2;
    
    //branch address
    assign branch_address = pc_plus4 + (imm_value_wire << 2); //where does pc_plus4 come from.
    
    //branch taken
    assign eq_test_wire = ((reg1_wire^reg2_wire)==32'd0) ? 1'b1: 1'b0;
    assign branch_taken = branch_wire && eq_test_wire;
    
    //reg1 and reg2
    register_file register_file_inst (
        .clk(clk),
        .reset(reset),  
        .reg_write_en(mem_wb_reg_write),  
        .reg_write_dest(mem_wb_write_reg_addr),  
        .reg_write_data(mem_wb_write_back_data),
        .reg_read_addr_1(instr[25:21]), //not sure which is bound to which
        .reg_read_addr_2(instr[20:16]), //not sure which is bound to which
        .reg_read_data_1(reg1_wire),  
        .reg_read_data_2(reg2_wire));
    assign reg1 = reg1_wire;
    assign reg2 = reg2_wire;
    
    //imm_value
    sign_extend sign_ex_inst (
        .sign_ex_in(instr[15:0]),
        .sign_ex_out(imm_value_wire));
    assign imm_value = imm_value_wire;
    
    //destination_reg
    mux2 #(.mux_width(5)) jump_mux
    (   .a(instr[20:16]),
        .b(instr[15:11]),
        .sel(reg_dst_wire),
        .y(destination_reg));
    
    
    
       
endmodule
