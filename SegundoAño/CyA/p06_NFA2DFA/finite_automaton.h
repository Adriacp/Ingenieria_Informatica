// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo finite_automaton.cc: Archivo con la declaracion de la clase FiniteAutomaton.
// Contiene la declaración de la clase FiniteAutomaton
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#ifndef FINITE_AUTOMATON_H_
#define FINITE_AUTOMATON_H_

#include "language.cc"
#include "transition.cc"
#include "subconjunto.cc"
#include <map>
#include <string>
#include <fstream>

class FiniteAutomaton {

  public:

  //Constructor 
  FiniteAutomaton(std::ifstream& my_file);

  //Funcion que procesa las transiciones
  std::set<Node> ProcessTransition(Node& node, const Symbol& symbol);

  //Funcion que procesa las epsilon clausuras
  void EpsilonClosure(std::set<Node>& nodes);

  //Funcion que comprueba si una cadena es aceptada
  bool IsChainAccepted(std::set<Node>& nodes);

  //Funcion evalua si una cadena es aceptada
  bool EvaluateChain(Chain& chain);
  
  //Funcion que muestra por pantalla los estados de muerte del automata
  void Killstates();

  void ShowLanguage();
  void ShowNodeNumber();
  void ShowStartNode();
  void ShowAutomaton();
  void ConstruccionSubconjuntos(std::ofstream&);
  void Escribir(std::ofstream&, std::set<std::set<Node>>&, std::map<std::pair<std::set<Node>, Symbol>, std::set<Node>>&);
  void Move(std::set<Node>& nodes, const Symbol& symbol);
  std::set<Node> UnicaTransition(Node&, const Symbol&);

  private:
  std::multimap<Node,Transition> finite_automaton_; 
  int node_number_;
  Node start_node_;
  Language automaton_language_;
};

#endif //FINITE_AUTOMATON_H_