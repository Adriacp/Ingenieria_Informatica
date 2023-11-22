// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo finite_automaton.cc: Archivo con la declaracion de la clase Transition.
// Contiene la declaración de la clase Transition
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "node.cc"

class Transition {

  public:

  //Constructores
  Transition(int starting_node, bool node1_type, Symbol& symbol, int ending_node, bool ending_node_type);
  Transition(Node& node, Symbol& symbol, Node& ending_node);
  Transition(Transition& transition);

  //Getters/Setters
  Node GetTransition() const;
  Symbol GetTransitionSymbol() const;
  Node GetStartNode() const;

  private:
  
  Node start_node_;
  Symbol symbol_;
  Node end_node_;

};

#endif //TRANSITION_H_