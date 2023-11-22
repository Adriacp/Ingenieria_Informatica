module sum4_v2(output wire[3:0] S, output wire c_out, input wire[3:0] A, input wire[3:0] B, input wire c_in);

  wire c_out0, c_out1, c_out2;
  assign {c_out0, S[0]} = A[0] + B[0] + c_in;
  assign {c_out1, S[1]} = A[1] + B[1] + c_out0;
  assign {c_out2, S[2]} = A[2] + B[2] + c_out1;
  assign {c_out, S[3]} = A[3] + B[3] + c_out2;

endmodule