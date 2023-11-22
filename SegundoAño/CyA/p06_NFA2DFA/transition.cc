// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo finite_automaton.cc: Archivo con la declaracion de la clase transition.
// Contiene la definicion de la clase FiniteAutomaton
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#include "transition.h"

//Contructor dado parametros
//Parametros: starting_node(nombre nodo 1) / node1_type (tipo del nodo) / symbol (simbolo de transicion) / ending_node (nombre al nodo al que transita)
Transition::Transition(int starting_node, bool node1_type, Symbol& symbol, int ending_node, bool ending_node_type) {
  Node initial_node(starting_node, node1_type);
  Node end_node(ending_node, ending_node_type);
  start_node_ = initial_node;
  symbol_ = symbol;
  end_node_ = end_node;
}

//Contructor dado un nodo como inicio del transicion
//Parametros: node (nodo inicial) / symbol (simbolo de transicion) / ending_node (nombre al nodo al que transita)
Transition::Transition(Node& node, Symbol& symbol,Node& ending_node) {
  start_node_ = node;
  symbol_ = symbol;
  end_node_ = ending_node;
}

//Contructor de copia
//Parametros: transition 
Transition::Transition(Transition& transition) {
  start_node_ = transition.GetStartNode();
  symbol_ = transition.GetTransitionSymbol();
  end_node_ = transition.GetTransition();
}

//Funcion que devuelve el nodo al que transita
Node Transition::GetTransition() const {
  return end_node_;
}

//Funcion que devuelve el nodo de transicion
Symbol Transition::GetTransitionSymbol() const {
  return symbol_;
}

//Funcion que devuelve el nodo de inicios
Node Transition::GetStartNode() const {
  return start_node_;
}
