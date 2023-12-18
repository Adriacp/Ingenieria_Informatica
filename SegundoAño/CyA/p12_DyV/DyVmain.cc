// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: EMST
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/12/2023
// Archivo EMSTmain.cpp: Archivo principal
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 07/12/2023 - Creación del código

#include <iostream>
#include <fstream>

#include "tools.cc"
#include "point_set.h"

bool opciond = false;
/// @brief Función principal que se encarga de invocar a las funciones para el correcto funcionamiento del programa
/// @param argc numero de parámetros pasados por línea de comandos
/// @param argv array con los parámetros pasados por línea de comandos
/// @return codigo de error
int main(int argc, char* argv[]) {
 //Usage
  Usage(argc, argv);
 //abrir el archivo
 std::string compare{argv[1]};
 if(compare == "-d") {
    opcionD = true;
 }
 std::string pointfilename;
 if(opcionD) {
    pointfilename= argv[2];
 } else {
    pointfilename = {argv[1]};
 }
  std::ifstream pointfile;
  CheckOpening(pointfile, pointfilename);
  CyA::point_vector vector_puntos;
  pointfile >> vector_puntos;
  CyA::point_set set_puntos(vector_puntos);
  set_puntos.quickHull();
  if(opcionD) {
  std::ofstream outFile(argv[3]);
  if (!outFile.is_open()) {
      std::cerr << "Error al abrir el archivo de salida." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  int numero_it = vector_puntos.size();
  std::string outfile_dot_str{argv[4]};
  GenerateDotFile(outfile_dot_str, set_puntos, numero_it);
  set_puntos.write_hull(outFile);

 outFile.close();
    
  } else {
    std::ofstream outFile(argv[2]);
    if(!outFile.is_open()) {
        std::cerr << "error al abrir el archivo de salida.\n";
        exit(EXIT_FAILURE);
    }

    set_puntos.write_hull(outFile);

    outFile.close();
  }

 return EXIT_SUCCESS;
}