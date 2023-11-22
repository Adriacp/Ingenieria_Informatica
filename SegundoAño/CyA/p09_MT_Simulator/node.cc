// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9:  Simulación de maquinas de Turing
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo estado.cc: Archivo con la definicion de la clase estado.cc
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include "node.h"

/// @brief constructor por defecto de la clase Node
/// @param  void
Node::Node(void) {
  identificator_ = -1; //por defecto
}

/// @brief constructor con un int como parametro
/// @param identificator nombre del nodo
Node::Node(int identificator) {
  identificator_ = identificator;
}

/// @brief constructor de copia de la clase node
/// @param identificator nodo al que copiar
Node::Node(const Node &identificator) {
  identificator_ = identificator.GetId();
}

/// @brief getter del nombre del node
/// @param  void
/// @return devuelve el nombre del nodo
const int Node::GetId(void) const {
  return identificator_;
}

/// @brief sobrecarga del operador < para usar los sets
/// @param node 
/// @return devuelve la comparación booleana
bool Node::operator<(const Node& node) const {
  return node.GetId() > identificator_;
}

/// @brief sobrecara del operador == para poder igualar dos nodes
/// @param node1 
/// @param node2 
/// @return devuelve el bool de la igualacion entre los nombres.
bool operator==(const Node& node1, const Node& node2) {
  return (node1.GetId() == node2.GetId());
}

/// @brief Sobrecarga del operador << para poder pasarlo por pantalla
/// @param os std::ostream
/// @param n node
/// @return os
std::ostream &operator<<(std::ostream &os, const Node& n) {
  os << "q" << n.GetId();
  return os;
}