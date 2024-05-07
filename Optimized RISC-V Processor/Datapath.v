////   Data Path /////
module data_path #(
    parameter PC_W = 8,       // Program Counter
    parameter INS_W = 32,     // Instruction Width
    parameter RF_ADDRESS = 5, // Register File Address
    parameter DATA_W = 32,    // Data WriteData
    parameter DM_ADDRESS = 9, // Data Memory Address
    parameter ALU_CC_W = 4    // ALU Control Code Width
 )(
    input                  clk ,    // CLK in datapath figure
    input                  reset,   // Reset in datapath figure      
    input                  reg_write,   // RegWrite in datapath figure
    input                  mem2reg,     // MemtoReg in datapath figure
    input                  alu_src,     // ALUSrc in datapath figure 
    input                  mem_write,   // MemWrite in datapath figure  
    input                  mem_read,    // MemRead in datapath figure          
    input  [ALU_CC_W-1:0]  alu_cc,      // ALUCC in datapath figure
    output          [6:0]  opcode,      // opcode in dataptah figure
    output          [6:0]  funct7,      // Funct7 in datapath figure
    output          [2:0]  funct3,      // Funct3 in datapath figure
    output   [DATA_W-1:0]  alu_result   // Datapath_Result in datapath figure
 );
    //PATHS
    wire [7:0]q;
    wire [31:0]instruction;
    wire [31:0]MUX2_Out;
    wire [31:0]rg_rd_data1;
    wire [31:0]rg_rd_data2;
    wire [31:0]ImmOut;
    wire [31:0]Y;
    wire [31:0]ALU_Out;
    wire Carry_Out;
    wire Zero;
    wire Overflow;
    wire [31:0]read_data;
    
    reg [7:0]pc_current;
    
    initial begin
        pc_current <= PC_W;
    end
         
        FlipFlop FlipFlopInst(
            .clk(clk),
            .reset(reset),
            .d(pc_current),
            .q(q)
            ); 
        
        InstMem InstMemInst(
            .addr(q),
            .instruction(instruction)
            );
        
        RegFile RegFileInst(
            .clk(clk),
            .reset(reset),
            .rg_wrt_en(reg_write),
            .rg_wrt_addr(instruction[11:7]),
            .rg_rd_addr1(instruction[19:15]),
            .rg_rd_addr2(instruction[24:20]),
            .rg_wrt_data(MUX2_Out),
            .rg_rd_data1(rg_rd_data1),
            .rg_rd_data2(rg_rd_data2)
            );
        
        ImmGen ImmGenInst(
            .InstCode(instruction),
            .ImmOut(ImmOut)
            );
        
        MUX21 MUX21Inst(
            .D1(rg_rd_data2),
            .D2(ImmOut),
            .S(alu_src),
            .Y(Y)
            );
                
        alu_32 alu_32Inst(
            .A_in(rg_rd_data1),
            .B_in(Y),
            .ALU_Sel(alu_cc),
            .ALU_Out(ALU_Out),
            .Carry_Out(Carry_Out),
            .Zero(Zero),
            .Overflow(Overflow)
            );
        
        DataMem DataMemInst(
            .MemRead(mem_read),
            .MemWrite(mem_write),
            .addr(ALU_Out[8:0]),
            .write_data(rg_rd_data2),
            .read_data(read_data)
            );
            
        MUX21 MUX21Inst2(
            .D1(ALU_Out),
            .D2(read_data),
            .S(mem2reg),
            .Y(MUX2_Out)
            );
        
        always @(posedge clk)
            begin 
                pc_current = pc_current + 4;
            end
         
        assign opcode = instruction[6:0];
        assign funct3 = instruction[14:12];
        assign funct7 = instruction[31:25];
        assign alu_result = ALU_Out;
endmodule
