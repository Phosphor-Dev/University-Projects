`timescale 1ns / 1ps


module mips_32(
    input clk, reset,  
    output[31:0] result
    );
    
// define all the wires here. You need to define more wires than the ones you did in Lab2
    wire [9:0]pc_plus4_wire_if;
    wire [31:0]instr_wire_if;
    
    wire [9:0]if_id_pc_plus4_wire; //check width
    
    wire [31:0]if_id_instr_wire; //check width
    
    wire [31:0] reg1_wire_id;
    wire [31:0] reg2_wire_id;
    wire [31:0] imm_value_wire_id;
    wire [9:0] branch_address_wire_id;
    wire [9:0] jump_address_wire_id;
    wire branch_taken_wire_id;
    wire [4:0] destination_reg_wire_id;
    wire mem_to_reg_wire_id;
    wire [1:0] alu_op_wire_id;
    wire mem_read_wire_id;
    wire mem_write_wire_id;
    wire alu_src_wire_id;
    wire reg_write_wire_id;
    wire jump_wire_id;
    
    wire [31:0]id_ex_instr_wire;
    wire [31:0]id_ex_reg1_wire;
    wire [31:0]id_ex_reg2_wire;
    wire [31:0]id_ex_imm_value_wire;
    wire [4:0]id_ex_destination_reg_wire;
    wire id_ex_mem_to_reg_wire;
    wire [1:0]id_ex_alu_op_wire;
    wire id_ex_mem_read_wire;
    wire id_ex_mem_write_wire;
    wire id_ex_alu_src_wire;
    wire id_ex_reg_write_wire;
    
    wire Data_Hazard_wire;
    wire IF_Flush_wire;
    
    wire [31:0] alu_in2_out_wire_ex;
    wire [31:0] alu_result_wire_ex;
    
    wire [1:0] Forward_A_wire_fu;
    wire [1:0] Forward_B_wire_fu;
    
    wire [31:0]ex_mem_instr_wire;
    wire [4:0]ex_mem_destination_reg_wire;
    wire [31:0]ex_mem_alu_result_wire;
    wire [31:0]ex_mem_alu_in2_out_wire;
    wire ex_mem_mem_to_reg_wire;
    wire ex_mem_mem_read_wire;
    wire ex_mem_mem_write_wire;
    wire ex_mem_reg_write_wire;
    
    wire [31:0]mem_read_data_wire;
    
    wire [31:0]mem_wb_alu_result_wire;
    wire [31:0]mem_wb_mem_read_data_wire;
    wire mem_wb_mem_to_reg_wire;
    wire mem_wb_reg_write_wire;
    wire [4:0]mem_wb_destination_reg_wire;
    
    wire [31:0]write_back_data_wire;  
    
// Build the pipeline as indicated in the lab manual

///////////////////////////// Instruction Fetch    
    IF_pipe_stage IF_pipe_stage_inst(
        .clk(clk),
        .reset(reset),
        .en(Data_Hazard_wire),
        .branch_address(branch_address_wire_id),
        .jump_address(jump_address_wire_id),
        .branch_taken(branch_taken_wire_id),
        .jump(jump_wire_id),
        
        .pc_plus4(pc_plus4_wire_if),
        .instr(instr_wire_if)
    );
    
        
///////////////////////////// IF/ID registers   
    pipe_reg_en #(.WIDTH(10)) pipe_reg_en_if_id_pc_plus4(//check width
        .clk(clk),
        .reset(reset),
        .en(Data_Hazard_wire),
        .flush(IF_Flush_wire),
        .d(pc_plus4_wire_if),
        
        .q(if_id_pc_plus4_wire)
    );
    
    
    pipe_reg_en #(.WIDTH(32)) pipe_reg_en_if_id_instr(//check width
        .clk(clk),
        .reset(reset),
        .en(Data_Hazard_wire),
        .flush(IF_Flush_wire),
        .d(instr_wire_if),
        
        .q(if_id_instr_wire)
    );


///////////////////////////// Instruction Decode 
    ID_pipe_stage ID_pipe_stage_inst(
        .clk(clk),
        .reset(reset),
        .pc_plus4(if_id_pc_plus4_wire),
        .instr(if_id_instr_wire),
        .mem_wb_reg_write(mem_wb_reg_write_wire),
        .mem_wb_write_reg_addr(mem_wb_destination_reg_wire),
        .mem_wb_write_back_data(write_back_data_wire),
        .Data_Hazard(Data_Hazard_wire),
        .Control_Hazard(IF_Flush_wire),
        
        .reg1(reg1_wire_id),
        .reg2(reg2_wire_id),
        .imm_value(imm_value_wire_id),
        .branch_address(branch_address_wire_id),
        .jump_address(jump_address_wire_id),
        .branch_taken(branch_taken_wire_id),
        .destination_reg(destination_reg_wire_id), 
        .mem_to_reg(mem_to_reg_wire_id),
        .alu_op(alu_op_wire_id),
        .mem_read(mem_read_wire_id),  
        .mem_write(mem_write_wire_id),
        .alu_src(alu_src_wire_id),
        .reg_write(reg_write_wire_id),
        .jump(jump_wire_id)
    );

             
///////////////////////////// ID/EX registers      
    pipe_reg #(.WIDTH(32)) pipe_reg_id_ex_instr(
        .clk(clk),
        .reset(reset),
        .d(if_id_instr_wire),
        .q(id_ex_instr_wire)
    );
    
    
    pipe_reg #(.WIDTH(32)) pipe_reg_id_ex_reg1(
        .clk(clk),
        .reset(reset),
        .d(reg1_wire_id),
        .q(id_ex_reg1_wire)
    );
    
    
    pipe_reg #(.WIDTH(32)) pipe_reg_id_ex_reg2(
        .clk(clk),
        .reset(reset),
        .d(reg2_wire_id),
        .q(id_ex_reg2_wire)
    );
    
    
    pipe_reg #(.WIDTH(32)) pipe_reg_id_ex_imm_value(
        .clk(clk),
        .reset(reset),
        .d(imm_value_wire_id),
        .q(id_ex_imm_value_wire)
    );
    
    
    pipe_reg #(.WIDTH(5)) pipe_reg_id_ex_destination_reg(
        .clk(clk),
        .reset(reset),
        .d(destination_reg_wire_id),
        .q(id_ex_destination_reg_wire)
    );
    
    
    pipe_reg #(.WIDTH(1)) pipe_reg_id_ex_mem_to_reg(
        .clk(clk),
        .reset(reset),
        .d(mem_to_reg_wire_id),
        .q(id_ex_mem_to_reg_wire)
    );
    
    pipe_reg #(.WIDTH(2)) pipe_reg_id_ex_alu_op(
        .clk(clk),
        .reset(reset),
        .d(alu_op_wire_id),
        .q(id_ex_alu_op_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_id_ex_mem_read(
        .clk(clk),
        .reset(reset),
        .d(mem_read_wire_id),
        .q(id_ex_mem_read_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_id_ex_mem_write(
        .clk(clk),
        .reset(reset),
        .d(mem_write_wire_id),
        .q(id_ex_mem_write_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_id_ex_alu_src(
        .clk(clk),
        .reset(reset),
        .d(alu_src_wire_id),
        .q(id_ex_alu_src_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_id_ex_reg_write(
        .clk(clk),
        .reset(reset),
        .d(reg_write_wire_id),
        .q(id_ex_reg_write_wire)
    );
    
    

///////////////////////////// Hazard_detection unit   
    Hazard_detection Hazard_detection_inst (
        .id_ex_mem_read(id_ex_mem_read_wire),
        .id_ex_destination_reg(id_ex_destination_reg_wire),
        .if_id_rs(if_id_instr_wire[25:21]),
        .if_id_rt(if_id_instr_wire[20:16]),
        .branch_taken(branch_taken_wire_id),
        .jump(jump_wire_id),
        
        .Data_Hazard(Data_Hazard_wire),
        .IF_Flush(IF_Flush_wire)
    );
           
///////////////////////////// Execution
    EX_pipe_stage EX_pipe_stage_inst(
        .id_ex_instr(id_ex_instr_wire),
        .reg1(id_ex_reg1_wire),
        .reg2(id_ex_reg2_wire),
        .id_ex_imm_value(id_ex_imm_value_wire),
        .ex_mem_alu_result(ex_mem_alu_result_wire),
        .mem_wb_write_back_result(write_back_data_wire),
        .id_ex_alu_src(id_ex_alu_src_wire),
        .id_ex_alu_op(id_ex_alu_op_wire),
        .Forward_A(Forward_A_wire_fu), 
        .Forward_B(Forward_B_wire_fu),
        
        .alu_in2_out(alu_in2_out_wire_ex),
        .alu_result(alu_result_wire_ex)
    );
        
///////////////////////////// Forwarding unit
    EX_Forwarding_unit EX_Forwarding_unit_inst(
        .ex_mem_reg_write(ex_mem_reg_write_wire),
        .ex_mem_write_reg_addr(),
        .id_ex_instr_rs(id_ex_instr_wire[25:21]),
        .id_ex_instr_rt(id_ex_instr_wire[20:16]),
        .mem_wb_reg_write(mem_wb_reg_write_wire),
        .mem_wb_write_reg_addr(mem_wb_destination_reg_wire),
        
        .Forward_A(Forward_A_wire_fu),
        .Forward_B(Forward_B_wire_fu)
    );
        
     
///////////////////////////// EX/MEM registers
	pipe_reg #(.WIDTH(32)) pipe_reg_ex_mem_instr(
        .clk(clk),
        .reset(reset),
        .d(id_ex_instr_wire),
        .q(ex_mem_instr_wire)
    );
    
    pipe_reg #(.WIDTH(5)) pipe_reg_ex_mem_destination_reg(
        .clk(clk),
        .reset(reset),
        .d(id_ex_destination_reg_wire),
        .q(ex_mem_destination_reg_wire)
    );
    
    pipe_reg #(.WIDTH(32)) pipe_reg_ex_mem_alu_result(
        .clk(clk),
        .reset(reset),
        .d(alu_result_wire_ex),
        .q(ex_mem_alu_result_wire)
    );
    
    pipe_reg #(.WIDTH(32)) pipe_reg_ex_mem_alu_in2_out(
        .clk(clk),
        .reset(reset),
        .d(alu_result_wire_ex),
        .q(ex_mem_alu_in2_out_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_ex_mem_mem_to_reg(
        .clk(clk),
        .reset(reset),
        .d(id_ex_mem_to_reg_wire),
        .q(ex_mem_mem_to_reg_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_ex_mem_mem_read(
        .clk(clk),
        .reset(reset),
        .d(id_ex_mem_read_wire),
        .q(ex_mem_mem_read_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_ex_mem__mem_write(
        .clk(clk),
        .reset(reset),
        .d(id_ex_mem_write_wire),
        .q(ex_mem_mem_write_wire)
    );
    
    pipe_reg #(.WIDTH(1)) pipe_reg_ex_mem_reg_write(
        .clk(clk),
        .reset(reset),
        .d(id_ex_reg_write_wire),
        .q(ex_mem_reg_write_wire)
    );
    

    
///////////////////////////// memory    
    data_memory data_mem(
        .clk(clk),
        .mem_access_addr(ex_mem_alu_in2_out_wire),
        .mem_write_data(ex_mem_alu_result_wire),
        .mem_write_en(ex_mem_mem_write_wire),
        .mem_read_en(ex_mem_mem_read_wire),
        
        .mem_read_data(mem_read_data_wire)
    );
     

///////////////////////////// MEM/WB registers
	pipe_reg #(.WIDTH(32)) mem_wb_alu_result(
        .clk(clk),
        .reset(reset),
        .d(ex_mem_alu_result_wire),
        .q(mem_wb_alu_result_wire)
    );
    
    pipe_reg #(.WIDTH(32)) mem_wb_mem_read_data(
        .clk(clk),
        .reset(reset),
        .d(mem_read_data_wire),
        .q(mem_wb_mem_read_data_wire)
    );
    
    pipe_reg #(.WIDTH(1)) mem_wb_mem_to_reg(
        .clk(clk),
        .reset(reset),
        .d(ex_mem_mem_to_reg_wire),
        .q(mem_wb_mem_to_reg_wire)
    );
    
    pipe_reg #(.WIDTH(1)) mem_wb_reg_write(
        .clk(clk),
        .reset(reset),
        .d(ex_mem_reg_write_wire),
        .q(mem_wb_reg_write_wire)
    );
    
    pipe_reg #(.WIDTH(5)) mem_wb_destination_reg(
        .clk(clk),
        .reset(reset),
        .d(ex_mem_destination_reg_wire),
        .q(mem_wb_destination_reg_wire)
    );
    

///////////////////////////// writeback  
	mux2 #(.mux_width(32)) write_back_mux(
	    .a(mem_wb_alu_result_wire),
        .b(mem_wb_mem_read_data_wire),
        .sel(mem_wb_mem_to_reg_wire),
        .y(write_back_data_wire));
        
assign result = write_back_data_wire;
endmodule
