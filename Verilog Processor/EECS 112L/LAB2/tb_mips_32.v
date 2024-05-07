module tb_mips_32;
      reg clk;  
      reg reset;  
      // Outputs  
      wire [31:0] result;
       
      // Instantiate the Unit Under Test (UUT)  
      mips_32 uut (  
           .clk(clk),   
           .reset(reset),     
           .result(result)    
      );  
      
      real points = 0;
      
      initial begin  
           clk = 0;  
           forever #10 clk = ~clk;  
      end
        
      initial begin  
           // Initialize Inputs  
 
           reset = 1;  
           // Wait 100 ns for global reset to finish  
           #100;  
           reset = 0;  
           // store some data in data memory
           uut.datapath_unit.data_mem.ram[8]= 32'b00000000000000000000000000000000;// $t0
           uut.datapath_unit.data_mem.ram[8]= 32'b00000000000000000000000000000000;// $t1
           uut.datapath_unit.data_mem.ram[8]= 32'b00000000000000000000000000000000;// $t2
           uut.datapath_unit.data_mem.ram[16]= 32'b00000000000000000000000000000001;// $s0
           uut.datapath_unit.data_mem.ram[17]= 32'b00000000000000000000000000000000;// $s1
           uut.datapath_unit.data_mem.ram[18]= 32'b00000000000000000000000000000010;// $s2
           uut.datapath_unit.data_mem.ram[19]= 32'b00000000000000000000000000000001;// $s3
           uut.datapath_unit.data_mem.ram[20]= 32'b00000000000000000000000000000001;// $s4
           
          #2670;
          if(uut.datapath_unit.data_mem.ram[17]==32'b00000000000000000000000000000000) begin $display("ANDI 1		success!\n"); points =points + 1; end else $display("ANDI 1	 	failed!\n");           
      end  
endmodule