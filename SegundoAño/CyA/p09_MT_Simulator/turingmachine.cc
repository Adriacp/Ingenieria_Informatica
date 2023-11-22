// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9:  Simulación de maquinas de Turing
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo turingmachine.h: Archivo con la definicion de la clase turingmachine.h
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include "turingmachine.h"
#include <cctype>
#include <algorithm>
/// @brief funcion para poder imprimir sets de node
/// @param set set a imprimir
void PrintSet(std::set<Node> set) {
  for(auto itr = set.begin(); itr != set.end(); ++itr) {
    std::cout << *itr << " ";
  }
  std::cout << "\n";
}

//pipsas con piñas
/// @brief constructor de la clase TuringMachine con el input_file
/// @param input_TM archivo con la definicion de la maquina de turing
TuringMachine::TuringMachine(std::ifstream &input_TM) {
  header_ = 1; //posicion respecto al vector
  std::string line;
  //recibo el numero de nodos
  getline(input_TM, line);
  num_nodes = std::stoi(line);
  for(int i = 0; i < num_nodes; i++) {
    Node new_node(i);
    nodes_.insert(new_node);
  }
  //recibo el nodo de arranque
  getline(input_TM, line);
  Node initial(std::stoi(line));
  initial_ = initial;
  //recibo el numero de nodos de aceptacion
  getline(input_TM, line);
  line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
  for(long unsigned int i = 0; i < line.length(); i++) {
    end_nodes_.insert(line[i] - '0');
  } 
  //recibo el numero de tuplas
  getline(input_TM, line);
  tuplenum_ = std::stoi(line);
  for(int i = 0; i <= tuplenum_; i++) {
    getline(input_TM, line);
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    Node nodopartida(line[0] - '0');
    IsANode(nodopartida);
    Symbol symbol(line[1]);
    Symbol escritura(line[2]);
    Symbol movement(line[3]);
    IsAMovement(movement);
    Node endNode(line[4] - '0');
    IsANode(endNode);
    std::pair<Symbol, Symbol> primerpair (symbol, escritura);
    std::pair<Symbol, Node> segundopair (movement, endNode);
    std::pair<std::pair<Symbol, Symbol>, std::pair<Symbol, Node>> pairfinal (primerpair, segundopair);
    tuples_.emplace(nodopartida, pairfinal); //guardo en el map todas las tuplas.
  }
}

/// @brief funcion que comprueba que el simbolo enviado sea o no un movimiento valido
/// @param symbol symbolo
void TuringMachine::IsAMovement(Symbol &symbol) {
  bool result = false;
  if (symbol.GetSymbol() == 'R' || symbol.GetSymbol() == 'L' || symbol.GetSymbol() == 'S') result = true;
  if(result == false) {
    std::cerr << symbol << " no es un movimiento\n";
    exit(EXIT_FAILURE);
  }
}

/// @brief Comprobacion si es un nodo de la maquina
/// @param node 
void TuringMachine::IsANode(Node& node) {
  bool result = false;
  for(auto itr = nodes_.begin(); itr != nodes_.end(); ++itr) {
    if(node == *itr) result = true;
  }
  if(result == false) {
    std::cerr << node << " no es un nodo de la máquina\n";
    exit(EXIT_FAILURE);
  }
}

/// @brief Imprime un map
void TuringMachine::Imprimirmap() {
  for(auto itr = tuples_.begin(); itr != tuples_.end(); ++itr) {
    std::cout << itr->first << itr->second.first.first << itr->second.first.second << itr->second.second.first << itr->second.second.second << std::endl;
  }
}

/// @brief calcula el siguiente movimiento de la cabecera
/// @param actual 
void TuringMachine::CalculateMove(Node &actual) {
  for(auto itr = tuples_.lower_bound(actual); itr != tuples_.upper_bound(actual); ++itr) {
    if(itr->second.first.first == tape_[header_]) {
      tape_[header_] = itr->second.first.second;
      if(itr->second.second.first == 'R') header_++;
      if(itr->second.second.first == 'L') header_--;
      actual = itr->second.second.second;
      break;
    }
  }
}

/// @brief comprueba si tiene que salir del while
/// @param actual 
/// @return bool
bool TuringMachine::Comprobacion(Node& actual) {
  bool result = false;
  for(auto itr = tuples_.lower_bound(actual); itr != tuples_.upper_bound(actual); ++itr) {
    if(itr->second.first.first == tape_[header_]) result = true;
  }
  return result;
}

/// @brief Comprueba si el estado esta dentro de los aceptados
/// @param node 
/// @return bool
bool TuringMachine::IsAccepted(Node &node) {
  bool result = false;
  if(end_nodes_.count(node.GetId()) != 0) result = true;
  return result;
}

/// @brief Funcion para simular el comportamiento de una maquina de turing
/// @param input_tape 
void TuringMachine::Simulate(std::ifstream &input_tape) {
  std::string cadena;
  getline(input_tape, cadena);
  tape_.push_back('$');
  for(long unsigned int i = 0; i < cadena.length(); i++) {
    tape_.push_back(cadena[i]);
  }
  tape_.push_back('$'); //creo el vector con todos los symbolos
  Node actual(initial_);
  while(true) {
    Symbol simbolo(tape_[header_]);
    for(long unsigned int i = 0; i < tape_.size(); i++) {
      if (header_ == i) std::cout << " " << actual << " ";
      std::cout << tape_[i];
    }
    std::cout << std::endl;
    if(!Comprobacion(actual)) break;
    CalculateMove(actual);
  }
  if(IsAccepted(actual)) std::cout << "Cadena ACEPTADA\n";
  else std::cout << "Cadena RECHAZADA\n";

}