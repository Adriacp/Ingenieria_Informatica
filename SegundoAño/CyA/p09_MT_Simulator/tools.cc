// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 27/10/2023
// Archivo tools.cc: Archivo con la definicion de las funciones de Grammar2CNF.cc entre otros.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include <iostream>
#include <string>
#include <set>
#include "symbol.h"
#include <fstream>
#include "node.h"

/// @brief Funcion Usage para comprobar la correcta pasada de parámetros
/// @param argc Número de  parámetros pasados por línea de comandos
/// @param argv El vector ded char que guarda lo que pasas por línea de comandos
void Usage(int argc, char* argv[]) {
  std::string help_message{"Modo de empleo: ./TM_simulator input.tm input.tape\nPruebe ./TM_simulator --help para mas informacion\n"};
  if(argc < 2) {
    std::cerr << help_message;
    exit(EXIT_FAILURE);
  }
  std::string key_word{argv[1]};
  if(key_word == "--help") {
    std::cout << "El programa simula el comportamiento de una maquina de turing contenida en el input.tm\n"
                 "la cinta se encuentra en input.tape y la simulacion viene por la terminal\n";
    exit(EXIT_FAILURE);
  }
  
  if(argc != 3) {
    std::cerr << help_message;
    exit(EXIT_FAILURE);
  }
}

/// @brief Comprueba que el archivo se abra correctamente
/// @param file archivo que tiene que abrirse correctamente
/// @param file_name nombre del archivo
void CheckOpening(std::ifstream& file, std::string file_name) {
  
  file.open(file_name);

  if(!file) {
    std::cerr << "Error al abrir el archivo, comprueba el archivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }
}
