`timescale 1ns / 1ps


module IF_pipe_stage(
    input clk, reset,
    input en,
    input [9:0] branch_address,
    input [9:0] jump_address,
    input branch_taken,
    input jump,
    output [9:0] pc_plus4,
    output [31:0] instr
    );


//Regs and Wires
reg [9:0] pc; 
wire [9:0]pc_plus4_wire;
wire [9:0]branch_jump_wire;
wire [9:0]jump_pc_wire;

//PC Gen
assign pc_plus4_wire = pc + 4;
always @(posedge clk  or posedge reset)//What does en and input from jump MUX have to do with this?
begin   
    if(reset)   
       pc <= 10'b0000000000;     
    else if (en)
       pc <= jump_pc_wire;  
end  

//Modules
mux2 #(.mux_width(10)) branch_taken_mux //DONE
    (   .a(pc_plus4_wire),
        .b(branch_address),
        .sel(branch_taken),
        .y(branch_jump_wire));

mux2 #(.mux_width(10)) jump_mux  //Where does this output into?
    (   .a(branch_jump_wire),
        .b(jump_address),
        .sel(jump),
        .y(jump_pc_wire));

instruction_mem inst_mem (
    .read_addr(pc),
    .data(instr));

assign pc_plus4 = pc_plus4_wire;

endmodule
