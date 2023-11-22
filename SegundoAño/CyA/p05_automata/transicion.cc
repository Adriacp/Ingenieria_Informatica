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
#include "transicion.h"
#include<iostream>
#include<iterator>
#include<algorithm>
#include<set>

/*
void Transicion::imprimir() {
  std::cout << simbolo_;
  for(std::set<Estado>::iterator itr = set_de_estados_.begin(); itr != set_de_estados_.end(); itr++) {
    if(itr == set_de_estados_.end()--)
      std::cout << (*itr);
    else
      std::cout << (*itr) << " "; 
  }
}
*/

/*
std::ostream &operator<<(std::ostream &os, Transicion t) {
  t.imprimir();
  return os;

}
*/

Transicion::Transicion(char estado_inicial, bool tipo_estado1, char simbolo, int estado_final, bool tipo_estado_final) {
 Estado estado1(estado_inicial, tipo_estado1);
 Estado estado2(estado_final, tipo_estado_final);
 estado_inicial_ = estado1;
 simbolo_ = simbolo;
 estado_final_ = estado2;
}

Transicion::Transicion(Estado &estado, char simbolo, Estado &estado_final) {
  estado_inicial_ = estado;
  simbolo_ = simbolo;
  estado_final_ = estado_final;
}

//Constructor de copia
Transicion::Transicion(const Transicion &transicion) {
  estado_inicial_ = transicion.GetEstadoInicial();
  simbolo_ = transicion.GetSimboloTransicion();
  estado_final_ = transicion.GetTransicion();
}

const Estado Transicion::GetTransicion() const {
  return estado_final_;
}

const char Transicion::GetSimboloTransicion() const {
  return simbolo_;
}

const Estado Transicion::GetEstadoInicial() const {
  return estado_inicial_;
}

void Transicion::print() {
  std::cout << estado_inicial_ << " " << simbolo_ << " " << estado_final_;
}

std::ostream &operator<<(std::ostream &os,Transicion &t) {
  t.print();
  return os;
}