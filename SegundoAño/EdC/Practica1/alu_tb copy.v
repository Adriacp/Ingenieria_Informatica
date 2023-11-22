// Testbench para modulo alu
`timescale 1 ns / 10 ps //Directiva que fija la unidad de tiempo de simulación y la precision de la unidad
module alu_tb;
//declaracion de señales
reg [1:0] t_Op;
reg t_l, t_cin;
reg [3:0] t_A, t_B; 
wire [3:0] t_R;
wire t_z, t_c, t_s;

// error de cualquier tipo, de resultado, de linea zero, de signo y carry

//instancia del modulo a testear
alu mat(t_R, t_z, t_c, t_s, t_A, t_B, t_cin, t_Op, t_l);


initial
begin
	$dumpfile("alu.vcd");
	$dumpvars;

	t_l = 1'b1;
		t_Op = 2'b10;
			t_cin = 1'b1;
		    	t_A = 4'b1111;
					t_B = 4'b0011;
					#20;

  	//fin simulacion
  	$finish;
end

// Tarea para hacer la comprobación automática de resultados

endmodule