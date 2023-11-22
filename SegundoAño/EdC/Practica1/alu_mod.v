module alu(output wire [3:0] R, output wire zero, c_out, sign, input wire [3:0] A, B, input wire c_in, input wire [1:0] ALUOP, input wire l);

  wire [3:0] OutOp1, OutOp2, Outsum4, Outul4;
  ab2op ab2op1(OutOp1, OutOp2, A, B, l, ALUOP);

//sumador y unidad logica

  sum4 sum4c_in(Outsum4, c_out, OutOp1, OutOp2 c_in);
  ul ul4ALUOP(Outul4, OutOp1, OutOp2, ALUOP);

  mux2_4 mux2_4l(R, Outsum4, Outul4, l);

  assign sign = R[3];
  assign zero = (~R[3]) & (~R[2]) & (~R[1]) & (~R[0]);

endmodule