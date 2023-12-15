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
#include <iomanip>

#include "point_set.h"

#define MAX_SZ 3
#define MAX_PREC 0

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

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);
std::ostream& operator<<(std::ostream& os, const CyA::line& l);
std::ostream& operator<<(std::ostream& os, const CyA::point& p);
std::istream& operator>>(std::istream& is, CyA::point_vector& ps);
std::istream& operator>>(std::istream& is, CyA::point& p);


std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps) {
    os << ps.size() << std::endl;

    for (const CyA::point &p : ps) {
        os << p << std::endl;
    }

    return os;
}


std::ostream& operator<<(std::ostream& os, const CyA::line& l) {
    os << "(" << l.first.first << ", " << l.first.second << ") " << "(" << l.second.first << ", " << l.second.second << ")\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const CyA::point& p) {
    
    os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.first << "\t" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.second;

    return os;
}

std::istream& operator>>(std::istream& is, CyA::point_vector& ps) {
    int n;
    is >> n;

    ps.clear();

    for (int i = 0; i < n; ++i) {
        CyA::point p;
        is >> p;

        ps.push_back(p);
    }

    return is;
}

std::istream& operator>>(std::istream& is, CyA::point& p) {
    is >> p.first >> p.second;

    return is;
}