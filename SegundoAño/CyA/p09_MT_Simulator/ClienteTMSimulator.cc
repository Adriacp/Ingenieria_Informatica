// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9:  Simulación de maquinas de Turing
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo ClienteTMSimulator.cc: Archivo con el main del TMSimulator
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include "tools.cc"
#include "turingmachine.h"

int main(int argc, char* argv[]) {
  
  Usage(argc, argv);
  std::string tm_file_name{argv[1]};
  std::ifstream tm_file;
  CheckOpening(tm_file, tm_file_name);
  TuringMachine TM(tm_file);
  std::string tape_file_name{argv[2]};
  std::ifstream tape_file;
  CheckOpening(tape_file, tape_file_name);
  TM.Simulate(tape_file);
  
  return 0;

}