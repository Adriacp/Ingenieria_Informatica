module regA(input wire clk, ResetA, CargaA, input wire [3:0] entA, output wire [3:0] q);
//Registro A de 4 bits, soporta Carga de entA y reseteo

ffdc ffa0(clk, ResetA, CargaA, entA[0], q[0]);
ffdc ffa1(clk, ResetA, CargaA, entA[1], q[1]);
ffdc ffa2(clk, ResetA, CargaA, entA[2], q[2]);
ffdc ffa3(clk, ResetA, CargaA, entA[3], q[3]);

endmodule

