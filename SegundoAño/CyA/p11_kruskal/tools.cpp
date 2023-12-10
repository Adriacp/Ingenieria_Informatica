// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: EMST
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/12/2023
// Archivo tools.cpp: Archivo de funciones utiles para el código
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 07/12/2023 - Creación del código

#include <iostream>
#include <fstream>

#include "point_types.hpp"
#include "point_set.hpp"

/// @brief funcion usage para comprobar el correcto paso de parámetros
/// @param argc numero de parámetros
/// @param argv array con los parámetros
void Usage(int argc, char* argv[]) {
  if(argc < 2 || argc > 3) {
    std::cerr << "Error en los parámetros, pruebe ./EMST --help para ayuda\n";
    exit(EXIT_FAILURE);
  }
  std::string key_word{argv[1]};
  if (key_word == "--help") {
    std::cout << "Este programa se ejecuta de la siguiente forma:\n"
                 "./EMST input.txt output.txt\n";
    exit(EXIT_SUCCESS);
  }
}

/// @brief Función para comprobar y abrir correctamente el archivo
/// @param file archivo a abrir
/// @param file_name nombre del archivo
void CheckOpening(std::ifstream& file, std::string file_name) {
  
  file.open(file_name);

  if(!file) {
    std::cerr << "Error al abrir el archivo, comprueba el archivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }
}

CyA::point_vector CrearVector(std::ifstream& pointfile) {
  int num_puntos;
  pointfile >> num_puntos;

  CyA::point_vector vector_de_puntos;

  double a, b;

  for(int i = 0; i < num_puntos; ++i) {
    pointfile >> a >> b;
    vector_de_puntos.push_back(std::make_pair(a, b));
  }
  pointfile.close();

  return vector_de_puntos;
}