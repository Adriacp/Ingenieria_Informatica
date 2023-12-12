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

#include "tools.cpp"
#include "point_types.hpp"
#include "point_set.hpp"

/// @brief Función principal que se encarga de invocar a las funciones para el correcto funcionamiento del programa
/// @param argc numero de parámetros pasados por línea de comandos
/// @param argv array con los parámetros pasados por línea de comandos
/// @return codigo de error
int main(int argc, char* argv[]) {
 //Usage
  Usage(argc, argv);
 //abrir el archivo
  std::string pointfilename{argv[1]};
  std::ifstream pointfile;
  CheckOpening(pointfile, pointfilename);
 //hacer la funcion de transformacion
 //sacar del archivo los puntos, transformarlos a points y despues esos meterlos en un point_vector
 /* IMPRESION
     for (const auto& punto : vector_de_puntos) {
        std::cout << "(" << punto.first << ", " << punto.second << ")" << std::endl;
    }
*/
    CyA::point_vector vector_de_puntos;
    point_set conjunto_de_puntos(vector_de_puntos);
    pointfile >> vector_de_puntos;
 //imprimir el archivo en otro
    conjunto_de_puntos.EMST();
    std::ofstream outFile(argv[2]);

    if (!outFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
    }

    outFile.close();

 return EXIT_SUCCESS;
}