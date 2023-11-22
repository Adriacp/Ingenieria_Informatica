
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

/// @brief constructor de Symbol con un string
/// @param symbol objeto tipo Symbol
Symbol::Symbol(std::string& symbol) {
  for (long unsigned int i = 0; i < symbol.length(); ++i) {
    symbol_ += symbol[i];
  }
}

/// @brief sobrecarga del constructor con un string
/// @param symbol string que llega
Symbol::Symbol(const std::string& symbol) {
  for(long unsigned int i = 0; i < symbol.length(); ++i) {
    symbol_ += symbol[i];
  }
}

/// @brief constructor de copia de la clase Symbol
/// @param symbol objeto tipo Symbol
Symbol::Symbol(const Symbol &symbol) {
  symbol_ = symbol.GetSymbol();
}

/// @brief Getter de la clase Symbol
/// @return devuelve un objeto symbol_
const char Symbol::GetSymbol() const {
  return symbol_;
}

/// @brief sobrecarga del operador = para la clase symbol
/// @param symbol1 symbol al que queremos igualar
void Symbol::operator=(Symbol symbol1) {
  symbol_ = symbol1.GetSymbol();
}

/// @brief sobrecarga del operator = para un char
/// @param a char
void Symbol::operator=(char a) {
  symbol_ = a;
}

//Sobrecarga del operador <<
std::ostream &operator<<(std::ostream &os, const Symbol& a) {
  os << a.GetSymbol();
  return os;
}

//Sobrecarga del operador <
bool Symbol::operator<(const Symbol& symbol) const {
  return symbol.GetSymbol() > symbol_;
}