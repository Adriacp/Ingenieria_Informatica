module ffdc #(parameter retardo = 1)(input wire clk, reset, carga, d, output reg q);
//reset asíncrono, carga síncrona
always @(posedge clk, posedge reset)
  if (reset)
    q <= #retardo 1'b0; //asignación no bloqueante q=0
  else
    if (carga)
      q <= #retardo d; //asignación no bloqueante q=d
endmodule
