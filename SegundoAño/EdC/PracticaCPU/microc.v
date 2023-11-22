module microc(output wire [5:0] Opcode, output wire zero, input wire clk, reset, s_inc, s_inm, we, wez, input wire [2:0] ALUOp);
//Microcontrolador sin memoria de datos de un solo ciclo

registro PC(10, OutPC, clk, reset, outMUX);
memprog MEM(OutMEM, clk, OutPC);

wire Inm[7:0], RA2[3:0], WA3[3:0], RA1[3:0], Dir_salto[9:0], RD1[7:0], RD2[7:0];

assign Inm[7:0] = OutMEM[11:4];
assign RA2[3:0] = OutMEM[7:4];
assign WA3[3:0] = OutMEM[3:0];
assign RA1[3:0] = OutMEM[11:8];

assign Dir_salto[9:0] = OutMEM[9:0];

mux2 MUX(10, outMUX, Dir_salto, outSUM, s_inc);
sum SUM(outSUM, 10'b0000000001, outPC);

mux2 MUX2(10, OutMUX2, RA1, WA3, s_inm);
regfile BancoRegistros(RD1, RD2, clk, we, OutMUX2, RA2, WA3, WD3);

mux2 MUX3(10, OutMUX3, RD2, Inm, s_inm);
alu ALU(WD3, zALU, RD1, OutMUX3, ALUOp);

ffd FFZ(clk, reset, zAlu, wez, zFFZ);
assign zero = zFFZ;


endmodule
