// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo alphabet.cc: Archivo con la definicion de los metodos de la clase alphabet.cc
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include "alphabet.h"

/// @brief constructor de copia de la clase Alphabet
/// @param a un objeto de la clase alphabet
Alphabet::Alphabet(const Alphabet &a) {
  alphabet_ = a.GetAlphabet();
  size_ = a.GetSize();
}

/// @brief Getter del set alphabet_
/// @return devuelve el atributo de la clase alphabet_
const std::set<Symbol> Alphabet::GetAlphabet() const {
  return alphabet_;
}

/// @brief Getter del tamaño del alphabet_
/// @return devuelve el atributo size_
const int Alphabet::GetSize() const {
  return alphabet_.size();
}

/// @brief Método para insertar objetos tipo Symbol en el alphabet_
/// @param symbol objeto tipo Symbol a insertar
void Alphabet::insert(Symbol& symbol) {
  alphabet_.insert(symbol);
}

/// @brief metodo para buscar si un symbol esta en el alphabet
/// @param symbol symbol a buscar
/// @return devuelve el booleano
bool Alphabet::find(Symbol &symbol) {
  bool resultado = false;
  if(alphabet_.count(symbol))
    resultado = true;
  return resultado;
}

/// @brief Funcion begin de alphabet aprovechando el begin del set
/// @return retorna alphabet.begin()
std::set<Symbol>::iterator Alphabet::begin() {
  return alphabet_.begin();
}

/// @brief Funcion end de alphabet aprovechando el end del set
/// @return retorna alphabet.end()
std::set<Symbol>::iterator Alphabet::end() {
  return alphabet_.end();
}

/// @brief sobrecarga del operador << para poder impirmir por pantalla alphabetos más cómodamente
/// @param os parámetro ostream necesario para la impresión
/// @param alphabet objeto de la clase alphabet a imprimir
/// @return devuelve os el objeto ostream
std::ostream& operator<<(std::ostream& os, const Alphabet alphabet) {
  for(std::set<Symbol>::iterator itr = alphabet.alphabet_.begin(); itr != alphabet.alphabet_.end(); ++itr) {
    os << itr->GetSymbol() << std::endl;
  }
  return os;
}
