module mux4_1(output reg out, input wire a, b, c, d, input wire [1:0] S);
always @(a or b or c or d or S)
  case (S)
    2'b00: out = a;
    2'b01: out = b;
    2'b10: out = c;
    2'b11: out = d;
  endcase

endmodule