module cl(output wire out, input wire a, b, input wire [1:0] S);
  
  wire c_and, c_or, c_xor, c_not;
  assign c_and = a & b;
  assign c_or = a|b;
  assign c_xor = a^b;
  assign c_not = ~a;
  mux4_1 multiplexor(out, c_and, c_or, c_xor, c_not, S);
  
endmodule