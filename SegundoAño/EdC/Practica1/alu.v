module alu(output wire [3:0] R, output wire zero, c_out, sign, input wire [3:0] A, B, input wire c_in, input wire [1:0] ALUOP, input wire l);

  assign add1 = l | ALUOP[0] | ALUOP[1];
  assign op1_A = l | ((~ALUOP[0]) & ALUOP[1]); 
  assign op2_B = l | ((~ALUOP[0]) & ALUOP[1]);
  assign cpl = (~l)&(~ALUOP[1])&ALUOP[0];
  wire [3:0] Outadd1, Outop1_A, Outop2_B, Outcompl1, Outsum4, Outul4;


//OP1
  mux2_4 mux2_4add1(Outadd1, 4'b0000, 4'b0001, add1);
  mux2_4 mux2_4op1_A(Outop1_A, Outadd1, A, op1_A);


//OP2
  mux2_4 mux2_4op2_B(Outop2_B, A, B, op2_B);
  compl1 compl1cpl(Outcompl1, Outop2_B, cpl);

//sumador y unidad logica

  sum4 sum4c_in(Outsum4, c_out, Outop1_A, Outcompl1, c_in);
  ul ul4ALUOP(Outul4, Outop1_A, Outcompl1, ALUOP);

  mux2_4 mux2_4l(R, Outsum4, Outul4, l);

  assign sign = R[3];
  assign zero = (~R[3]) & (~R[2]) & (~R[1]) & (~R[0]);

endmodule