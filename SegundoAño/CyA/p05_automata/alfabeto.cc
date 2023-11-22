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
#include "alfabeto.h"
#include<iterator>
#include<algorithm>
#include<iostream>

void Alfabeto::Imprimir_alfabeto(void) {
  for(std::set<char>::iterator i = alfabeto_.begin() ; i != alfabeto_.end(); i++) {
    std::cout << *i;
  }
  std::cout << std::endl;
}

bool Alfabeto::Comprobar_simbolo(char simbolo) {
  bool resultado = false;
  for(std::set<char>::iterator i = alfabeto_.begin() ; i != alfabeto_.end(); i++) {
    resultado = (*i == simbolo);
  }
  return resultado;
}

std::set<char>::iterator Alfabeto::Begin(){
  return alfabeto_.begin();
}

std::set<char>::iterator Alfabeto::End() {
  return alfabeto_.end();
}

void Alfabeto::operator=(Alfabeto& alfabeto) {
  for(std::set<char>::iterator itr = alfabeto.Begin(); itr != alfabeto.End(); itr++) {
    alfabeto_.insert(*itr);
  }
}

bool Alfabeto::EstaEnLenguaje(char simbolo) {
  bool resultado = false;
    for(auto itr = alfabeto_.begin(); itr != alfabeto_.end(); ++itr) {
      if(*itr == simbolo) {
        resultado = true;
      }
    }
  return resultado;
}