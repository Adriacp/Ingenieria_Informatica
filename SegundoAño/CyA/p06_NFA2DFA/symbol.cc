// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo symbol.cc: Archivo con la definicion de los metodos de la clase symbol.
// Contiene la declaración de la clase symbol
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 23/09/2023 - Creación del código

#include "symbol.h"


//Constructor
//Parametros: simbolo que queremos crear
Symbol::Symbol(char symbol) {
  symbol_ = symbol;
}

Symbol::Symbol(std::string& symbol) {
  for (long unsigned int i = 0; i < symbol.length(); ++i) {
    symbol_ = symbol[i];
  }
}

//Sobrecarga del operador ==
const bool operator==(Symbol& a, Symbol& b) {
  return a.GetChar() == b.GetChar();
} 

//Sobrecarga del operador <<
std::ostream &operator<<(std::ostream &os, const Symbol& a) {
  os << a.GetChar();
  return os;
}

//Sobrecarga del operador <
bool Symbol::operator<(const Symbol& symbol) const {
  return symbol.GetChar() > symbol_;
}

//Getter del caracter
const char Symbol::GetChar() const {
  return symbol_;
}