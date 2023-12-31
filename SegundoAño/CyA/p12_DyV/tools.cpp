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
#include <map>

#include "point_set.h"

#define MAX_SZ 3
#define MAX_PREC 0

/// @brief funcion usage para comprobar el correcto paso de parámetros
/// @param argc numero de parámetros
/// @param argv array con los parámetros
void Usage(int argc, char* argv[]) {
  if(argc < 3 || argc > 5) {
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


/// @brief Funcion de sobrecarga del operador << sobre un point_vector
/// @param os salida
/// @param ps point_vector
/// @return os.
std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps) {
    os << ps.size() << std::endl;

    for (const CyA::point &p : ps) {
        os << p << std::endl;
    }

    return os;
}

/// @brief Funcion de sobrecarga del operador << sobre un line
/// @param os salida
/// @param l line
/// @return os.
std::ostream& operator<<(std::ostream& os, const CyA::line& l) {
    os << "(" << l.first.first << ", " << l.first.second << ") " << "(" << l.second.first << ", " << l.second.second << ")\n";
    return os;
}

/// @brief Funcion de sobrecarga del operador << sobre un point
/// @param os salida
/// @param p point
/// @return os.
std::ostream& operator<<(std::ostream& os, const CyA::point& p) {
    
    os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.first << "\t" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.second;

    return os;
}

/// @brief Funcion de sobrecarga del operador >> sobre un point_vector
/// @param is entrada
/// @param ps point_vector
/// @return is.
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

/// @brief Funcion de sobrecarga del operador >> sobre un point
/// @param is entrada
/// @param p point_vector
/// @return os.
std::istream& operator>>(std::istream& is, CyA::point& p) {
    is >> p.first >> p.second;

    return is;
}

void GenerateDotFile(std::string& outfile_dot_str, CyA::point_set& v, int numero_it) {
  std::ofstream outfile_dot(outfile_dot_str);

  std::map<int, CyA::point> mapeo_puntos;

  if (!outfile_dot.is_open()) {
    std::cerr << "Error al abrir el archivo.dot de salida.\n";
    exit(EXIT_FAILURE);
  }
  std::vector<int> puntos;
  
  outfile_dot << "graph Puntos {\n";


  for(int i = 0; i < v.get_input().size(); i++) {
    mapeo_puntos[i] = v.get_input()[i];
  }
  
  for(auto itr = mapeo_puntos.begin(); itr != mapeo_puntos.end(); itr++) {
    outfile_dot << itr->first << "[pos = \"" << itr->second.first << ", " << itr->second.second << "!\"]\n";
  } 

  outfile_dot << "\n";

  for(auto itr = mapeo_puntos.begin(); itr != mapeo_puntos.end(); itr++) {
    for(int i = 0; i < v.get_hull().size(); i++) {
      if(itr->second == v.get_hull()[i]) {
        puntos.push_back(i);
      }
    }
  }

  for(int i = 0; i < puntos.size(); i++) {
    outfile_dot << i;
    if(i % 2 != 0) outfile_dot << "\n";
    if(i < puntos.size()-1 && i % 2 == 0) {
      outfile_dot << " -- ";
    }
  }
  if(numero_it % 2 == 0) outfile_dot << puntos[puntos.size()-1] << " -- " << puntos[0];
  else outfile_dot << " -- " << puntos[0];
  
  outfile_dot << "\n";
  /*
  std::sort(vector_indices.begin(), vector_indices.end());
  vector_indices.erase(std::unique(vector_indices.begin(), vector_indices.end()), vector_indices.end());
  */

  //for(int i = 0; i < vector_indices.size(); i++) {
  //  std::cout << vector_indices[i];
  //}
  

  outfile_dot << "}\n";

  outfile_dot.close();
}