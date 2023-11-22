// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 5: Implementacios de un simulador de automatas finitos
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 19/09/2023
// Archivo cya-P05-automata-simulator
// Contiene la función main del proyecto.
// Para hacer un automata finito
// 17/09/2023 - Creación (primera versión) del código
#include "estado.h"
#include<iostream>

Estado::Estado(char nombre, bool aceptacion, int numero_transiciones, std::vector<char> transiciones) {
  nombre_ = nombre;
  aceptacion_ = aceptacion;
  numero_transiciones_ = numero_transiciones;
  //transiciones_ = transiciones;
}
/*
void Estado::Imprimir_vector() {
  for(long unsigned int i = 0; i < transiciones_.size(); i++) {
    std::cout << transiciones_[i] << " ";
  }
  std::cout << "\n";
}
*/

bool Estado::operator==(Estado p) const {
  return nombre_ == p.Get_nombre();
} 

bool Estado::operator<(Estado const &e) const {
  return nombre_ < e.nombre_ || nombre_ == e.nombre_;
}

std::ostream &operator<<(std::ostream &os, Estado p) {
  std::cout << p.Get_nombre();
  return os;
}
/*
void Estado::Insertar_transicion(char a) {
  transiciones_.push_back(a);
}
*/