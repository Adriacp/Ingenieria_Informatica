module compl2(output wire [3:0] Out, input wire [3:0] Inp, input wire cpl);

  wire [3:0] temp1;
  compl1 compl1_1(temp1, Inp, cpl);
  assign Out = temp1 + 4'b0001;

endmodule