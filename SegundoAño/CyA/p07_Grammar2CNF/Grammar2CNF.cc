// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 27/10/2023
// Archivo Grammar2CNF.cc : archivo con la funcion main
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include <iostream>
#include <fstream>
#include "grammar.h"
#include "tools.cc"

/// @brief funcion main del programa
/// @param argc cantidad de parámetros pasados por línea de comandos
/// @param argv array con todos los parámetros pasados por línea de comandos
/// @return devuelve el codigo de error
int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::string input_file_name{argv[1]};
  std::ifstream input_file;
  CheckOpening(input_file, input_file_name);
  Grammar grammar(input_file);
  std::string output_file_name{argv[2]};
  std::ofstream output_file;
  output_file.open(output_file_name); //abre o crea al archivo de salida
  grammar.CNF();
  output_file << grammar;
  return 0;
  }