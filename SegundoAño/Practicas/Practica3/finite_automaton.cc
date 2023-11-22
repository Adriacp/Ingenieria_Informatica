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
// Contiene la definicion de la clase FiniteAutomaton
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#include "finite_automaton.h"
#include <sstream>

//Constructor
//Parametros: my_file (stream de entrada)
FiniteAutomaton::FiniteAutomaton(std::ifstream& my_file) {
  std::set<Node> automaton_nodes;
  std::string symbol;
  std::string line;
  //Leemos la primera linea y la metemos en un stream de string
  std::getline(my_file, line);
  std::istringstream line_stream(line);
  //Leemos el stream de string y creamos el alfabeto para el automata
  while (line_stream >> symbol) {
    Chain chain(symbol);
    automaton_language_.Insert(chain);
  }

  //Leemos el total de nodos y guardamos
  int number_of_nodes;
  my_file >> number_of_nodes;
  node_number_ = number_of_nodes;

  //Leemos el nodo de inicio y lo guardamos
  int starting_node;
  my_file >> starting_node;
  
  //Ya que sabemos el numero total de nodos, leemos todas las lineas
  for (int i = 0; i < number_of_nodes; ++i) {
    int node;
    bool type;

    my_file >> node >> type;
    
    if (node == starting_node) {
      Node starter_node(node, type);
      start_node_ = starter_node;
    }

    if (node >= 0 && node <= node_number_ -1) {
      Node new_node(node, type);
      std::getline(my_file, line);
      automaton_nodes.insert(new_node);
    }
    
  }

  //Vuelta al inico
  my_file.seekg(0, std::ios::beg);
  
  //Leemos las tres primeras lineas
  for (int j = 0; j < 3; ++j)  {
    std::getline(my_file, line);
  }
  
  for (int k = 0; k < number_of_nodes; ++k) {
    int node, total_transitions;
    bool type;
    my_file >> node >> type >> total_transitions;
    if (total_transitions == 0) {
      Node loop_node(node,type);
      Symbol no_transition('\0');
      Transition loop(loop_node,no_transition,loop_node);
      finite_automaton_.emplace(loop_node,loop);
    }
    for (int l = 0; l < total_transitions; ++l) {
      int end_node;
      my_file >> symbol >> end_node;
      Node start_node;
      for (auto m = automaton_nodes.begin(); m!= automaton_nodes.end(); ++m) {
        if ( m->GetNode() == node ) {
          Node aux_node(m->GetNode(), m->GetType());
          start_node = aux_node;
          }
      }  
      Symbol transition_symbol(symbol);
      Chain aux_chain(transition_symbol);
      if (automaton_language_.IsInLanguage(aux_chain)) {
        for (auto m = automaton_nodes.begin(); m!= automaton_nodes.end(); ++m) {
          if ( m->GetNode() == end_node ) {
            Node ending_node(m->GetNode(), m->GetType());
            Transition transition(start_node, transition_symbol, ending_node);
            finite_automaton_.emplace(start_node,transition);
          }
        }
      }
    }
  }
  my_file.close();
}

//Funcion que procesa una transicion
//Parametros: node (nodo de inicio) / symbol (simbolo de la cadena)
std::set<Node> FiniteAutomaton::ProcessTransition(Node& node, Symbol& symbol) {
  //Nodos a los que transita, usamos un set ya que puede haber 1 o mas estados
  std::set<Node> next_nodes;
  //Recorremos las transiciones del nodo especificado
  for (auto i = finite_automaton_.lower_bound(node); i != finite_automaton_.upper_bound(node); ++i) {
    Transition current_transition(i -> second);
    //Si el simbolo de la cadena coincide con el simbolo de transicion
    Symbol aux_symbol(symbol);
    Chain aux_chain(aux_symbol);
    if ( current_transition.GetTransitionSymbol().GetChar() == symbol.GetChar() && automaton_language_.IsInLanguage(aux_chain)) {
      //Recorremos el automata para copiar el nodo de transicion
      for (auto j = finite_automaton_.begin(); j != finite_automaton_.end(); ++j) {
        //creamos el nodo siguiente
        Node aux_node(j -> first);
        //Si el nodo al que transita == nodo en el automata
        if (aux_node.GetNode() == current_transition.GetTransition().GetNode()) {
          //creamos el nuevo nodo y lo metemos en nuestro conjunto de nodos siguientes
          Node new_node(current_transition.GetTransition().GetNode(), aux_node.GetType());
          next_nodes.insert(new_node);
        }
      }
    }
  }
  return next_nodes;
}

//Funcion que calcula la epsilon clausura del set de nodos
//Parametros: nodes (conjunto de nodos actuales)
void FiniteAutomaton::EpsilonClosure(std::set<Node>& nodes) {
  //Simolo de transicion y conjunto de estados siguientes
  Symbol epsilon('&');
  std::set<Node> next_nodes;
  //Recorremos el conjunto de nodos actuales
  for (auto i = nodes.begin(); i != nodes.end(); ++i) {
    Node actual_node(*i);
    //Calculamos las transiciones con el simbolo epsilon de cada nodo de los nodos actuales
    next_nodes = ProcessTransition(actual_node,epsilon);
    for ( auto j = next_nodes.begin(); j != next_nodes.end(); ++j) {
      //Insertamos los nodos que no esten en los nodos actuales
      nodes.insert(*j);
    }
  }
}

//Funcion que comprueba si una cadena es aceptada por el automata
//Parametros: nodes (conjunto de nodos actuales)
bool FiniteAutomaton::IsChainAccepted(std::set<Node>& nodes) {
  bool accepted{false};
  //Recorremos el conjunto de nodos actuales
  for (auto i = nodes.begin(); i != nodes.end(); ++i) {
    Node actual_node(*i);
    //Si algun nodo del conjunto es de aceptacion, la cadena es aceptada
    if (actual_node.GetType() == 1) {
      accepted = true;
    }
  }
  return accepted;
}

//Funcion que evalua una cadena
//Parametros: cadena a ser evaluada
bool FiniteAutomaton::EvaluateChain(Chain& chain) {
  //Conjunto de nodos actuales y siguientes
  std::set<Node> current_nodes;
  std::set<Node> next_nodes;
  
  //Consideramos el estado inicial con epsilon clausura
  //Recorremos el automata para buscar el nodo de incio
  for (auto i = finite_automaton_.begin(); i != finite_automaton_.end(); ++i) {
    Node start_node(i->first);
    //Si es el nodo de inicio
    if (start_node.GetNode() == start_node_.GetNode()) {
      current_nodes.insert(start_node);
    }
  }
  //Calculamos la epsilon clausura
  EpsilonClosure(current_nodes);

  //Procesamos cada símbolo en la cadena
  for (int i = 0; i < chain.GetLenght(); ++i) {
    Symbol actual_symbol(chain[i]);
    next_nodes.clear();
    
    //Para cada estado actual, seguimos todas las transiciones posibles
    for (auto j = current_nodes.begin(); j != current_nodes.end(); ++j) {
      Node actual_node(*j);
      std::set<Node> transitions = ProcessTransition(actual_node, actual_symbol);
      for (auto k = transitions.begin(); k != transitions.end(); ++k) {
        next_nodes.insert(*k);
      }
    }

    // Realizamos el cierre-épsilon en los nuevos estados
    for (auto k = next_nodes.begin(); k != next_nodes.end(); ++k) {
      EpsilonClosure(next_nodes);
    }
    
    // Actualizamos el conjunto de estados actuales
    current_nodes = next_nodes;
  }
  
  // Verificamos si al menos uno de los estados actuales es de aceptación
  return IsChainAccepted(current_nodes);
}

void FiniteAutomaton::ShowLanguage() {
  std::cout << automaton_language_ << std::endl;
}

void FiniteAutomaton::ShowNodeNumber() {
  std::cout << node_number_ << std::endl;
}

void FiniteAutomaton::ShowStartNode() {
  std::cout << start_node_.GetNode() << std::endl;
}


void FiniteAutomaton::ShowAutomaton() {
  for (auto i = finite_automaton_.begin(); i != finite_automaton_.end(); ++i) {
    Node node;
    std::cout << "Nodo: " << (i->first).GetNode() << std::endl;
    Transition transition(i->second);
    std::cout << transition.GetStartNode().GetNode() << " " << transition.GetTransitionSymbol().GetChar() << " " << transition.GetTransition().GetNode() << std::endl;
  }
}
