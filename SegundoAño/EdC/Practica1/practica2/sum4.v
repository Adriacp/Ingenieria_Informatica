//Sumador de 4 bits con prediccion de acarreo, se obtienen tambien los acarreos para comprobarlos
module sum4(output wire[3:0] S, output wire[4:1] C, output wire c_out, input wire[3:0] A, input wire[3:0] B, input wire c_in);
//contenido
wire c1, c2, c3, c4;
//wire[4:1] C;
cla_4 cla(C[4:1], {g3, g2, g1, g0}, {p3, p2, p1, p0}, c_in);
fa_v3 fa0(S[0], c1, p0, g0, A[0], B[0], c_in);
fa_v3 fa1(S[1], c2, p1, g1, A[1], B[1], C[1]);
fa_v3 fa2(S[2], c3, p2, g2, A[2], B[2], C[2]);
fa_v3 fa3(S[3], c4, p3, g3, A[3], B[3], C[3]);
assign c_out = C[4];
endmodule

//Sumador completo (full-adder) de tres entradas de 1 bit realizado a partir de semisumadores con retardo y salidas p y g
module fa_v3(output wire sum, output wire c_out, output wire p, output wire g, input wire a, input wire b, input wire c_in);
//Declaración de conexiones internas:
wire sum_par, carry1, carry2;   //la suma parcial antes de sumar acarreo de entrada y los acarreos de los dos semisumadores
//Estructura interna: Instancias de puertas y sus conexiones 
ha_vr ha1(sum_par, carry1, a,    b     );  //Suma a y b y produce suma y acarreo parciales
ha_vr ha2(sum,     carry2, c_in, sum_par);  //Suma a la suma parcial anterior el acarreo de fuera y obtiene la suma de salida
or or1(c_out, carry1, carry2); //Realiza la OR entre los acarreos de los semisumadores para dar el de salida, la salida sería instantánea respecto a las entradas
or or2(p, a, b); //genera la p, señal de propagación de acarreo previo
and and1(g, a, b); //genera la g, señal de generación de acarreo en la etapa actual
endmodule

//Semisumador de dos entradas de 1 bit realizado a partir de puertas
module ha_vr(output wire sum, carry, input wire a, b);
//Estructura interna: Instancias de puertas y sus conexiones, se incluyen retardos
xor #1 xor1(sum, a, b); //el retardo va entre el nombre del modulo (solo modulos primitivos) y el de la instancia
and #1 and1(carry, a, b);
endmodule

//Bloque de predicción de acarreo de 4 bits en función de las variables pi y gi de cada bit
module cla_4(output wire[4:1] C, input wire[3:0] G, input wire[3:0] P, input wire c_in);
assign C[1] = G[0] | (P[0] & c_in);
assign C[2] = G[1] | (P[1] & G[0]) | (P[1] & P[0] & c_in);
assign C[3] = G[2] | (P[2] & G[1]) | (P[2] & P[1] & G[0]) | (P[2] & P[1] & P[0] & c_in);
assign C[4] = G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0]) | (P[3] & P[2] & P[1] & P[0] & c_in);
endmodule


