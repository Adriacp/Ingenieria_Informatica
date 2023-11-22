// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo finite_automaton.cc: Archivo con la declaracion de la clase Node.
// Contiene la definicion de la clase Node
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#include "node.h"

//Constructor por defecto
Node::Node(void) {
  node_ = -1;
  type_ = false;
}

//Constructor dado parametros
//Parametros: node, type
Node::Node(int node, bool type) {
  node_ = node;
  type_ = type;
}

//Funcion que devuelve el nodo
const int Node::GetNode() const {
  return node_;
}

//Funcion que devuelve el tipo del nodo
const bool Node::GetType() const {
  return type_;
}

//Sobrecarga operador < para usar sets
//Parametros: Nodo
bool Node::operator<(const Node& node) const {
  return node.GetNode() > node_;
}

std::ostream &operator<<(std::ostream &os, const Node& n) {
  os<< n.GetNode();
  return os;
}

bool operator==(const Node& node1, const Node& node2) {
  return (node1.GetNode() == node2.GetNode()) && node1.GetType() == node2.GetType();
}
//Constructor de copia
//Parametros: node a copiar
Node::Node(const Node& node) {
  node_ = node.GetNode();
  type_ = node.GetType();
}