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
#include<list>
#include <sstream>
#include<vector>
#include"subconjunto.h"

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
    //Chain chain(symbol);
    Symbol symbol1(symbol);
    automaton_language_.Insert(symbol1);
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
      Symbol aux_symbol(transition_symbol);
      if (automaton_language_.IsInLanguage(aux_symbol)) {
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
std::set<Node> FiniteAutomaton::ProcessTransition(Node& node, const Symbol& symbol) {
  //Nodos a los que transita, usamos un set ya que puede haber 1 o mas estados
  std::set<Node> next_nodes;
  //Recorremos las transiciones del nodo especificado
  for (auto i = finite_automaton_.lower_bound(node); i != finite_automaton_.upper_bound(node); ++i) {
    Transition current_transition(i -> second);
    //Si el simbolo de la cadena coincide con el simbolo de transicion
    Symbol aux_symbol(symbol);
    Symbol aux_symbol1(aux_symbol);
    if ( current_transition.GetTransitionSymbol().GetChar() == symbol.GetChar() && automaton_language_.IsInLanguage(aux_symbol1)) {
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

void PrintSet(std::set<Node> set);

std::set<Node> FiniteAutomaton::UnicaTransition(Node& node, const Symbol& symbol) {
  std::set<Node> Transition;
  for(auto itr = finite_automaton_.lower_bound(node); itr != finite_automaton_.upper_bound(node) ; ++itr) {
    if(itr->second.GetTransitionSymbol().GetChar() == symbol.GetChar()) {
      Transition.insert(itr->second.GetTransition());
    }
  }
  return Transition;
}

//Función para comprobar todos los posibles movimientos de un conjunto de estados con el simbolo enviado
//Parámetros: nodes (conjunto de nodos actuales)
//Parámetros: symbol (simbolo con el que queremos hacer la transicion)
void FiniteAutomaton::Move(std::set<Node>& nodes, const Symbol& symbol) {
  std::set<Node> next_nodes;
  //Recorremos el conjunto de nodos actuales
  for (auto i = nodes.begin(); i != nodes.end(); ++i) {
    Node actual_node(*i);
    //Calculamos las transiciones con el simbolo epsilon de cada nodo de los nodos actuales
    next_nodes = UnicaTransition(actual_node,symbol);
    
  }
  for ( auto j = next_nodes.begin(); j != next_nodes.end(); ++j) {
    //Insertamos los nodos que no esten en los nodos actuales
    nodes.insert(*j);
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

void PrintSet(std::set<Node> set) {
  for(auto itr = set.begin(); itr != set.end(); ++itr) {
    std::cout << itr->GetNode();
  }
}
/*
void FiniteAutomaton::ConstruccionSubconjuntos() {
  std::list<std::set<Node>> Cola; //Cola de ejecucion de los nodos del algoritmo
  std::set<std::set<Node>> EstadosDFA; //Estados finales que me quedane en el dfa
  std::set<Node> Actuales;
  Actuales.insert(start_node_);
  EpsilonClosure(Actuales);
 //crear Conjunto de estados no visitados y metemos el nodo inicial
 //while (queden estados no visitados) extrae un conjunto de estados no visitados y marcalo como visitado
 //hacer epsilon(move(del estado con cada simbolo del alfabeto))
 //si el estado resultante no esta en visitados, añadir a no visitados
 //el conjunto de estados que tengan el estado final, sera de aceptación
 //el inicial sera el que tenga al inicial
  
  std::set<Node> nodosActuales;
  nodosActuales.insert(start_node_);
  //std::map<int, std::pair<std::set<Node>, std::set<Node>>> estadosDFA;
  EpsilonClosure(nodosActuales);
  std::list<std::set<Node>> no_visitado;
  std::vector<std::set<Node>> visitados;
  std::vector<Transition> transiciones;
  //map<subconjunto, std::pair<symbol, subconjunto>>
  no_visitado.push_back(nodosActuales);
    //PrintSet(nodosActuales);
  std::multimap<std::set<Node>, std::pair<Symbol, std::set<Node>>> mapaDFA;
  while(!no_visitado.empty()) {
    std::set<Node> conjuntoActual;
    conjuntoActual = no_visitado.front();
    visitados.emplace_back(no_visitado.front());
    no_visitado.pop_front();
    for(auto i = automaton_language_.Begin(); i !=automaton_language_.End(); ++i) {
      std::set<Node> nuevoConjunto;
      nuevoConjunto = conjuntoActual;
      Move(nuevoConjunto, (*i));
      EpsilonClosure(nuevoConjunto);
      for(long unsigned int j = 0; j < visitados.size() ; ++j) {
        if(nuevoConjunto != visitados[j]) {
          no_visitado.push_back(nuevoConjunto);
          std::pair<Symbol, std::set<Node>> pareja ((*i), nuevoConjunto); //pair que contiene el simbolo y el set de nodos al que va
          mapaDFA.emplace(conjuntoActual, pareja); //mapa para tener las transiciones
        }
      }
    }
 }
 for(auto itr = mapaDFA.begin(); itr != mapaDFA.end(); ++itr) {
  for(auto i = mapaDFA.lower_bound(itr->first); i != mapaDFA.upper_bound(itr->first); ++i) {
    std::cout << "simbolo: " << i->second.first << std::endl << "estado en el que estoy: ";
    PrintSet(itr->first);
    std::cout << "\nconjunto de estados al que va: ";
    PrintSet(i->second.second);
    std::cout << std::endl;
  }
 }
}
*/

bool Condiciones(std::set<Node> T, std::set<std::set<Node>> estadosDFA, std::vector<std::set<Node>> visitados, std::list<std::set<Node>> no_visitados) {
  bool condicion1 = false;
  bool condicion2 = true;
  bool condicion3 = false;
  
  for(auto i = estadosDFA.begin(); i != estadosDFA.end(); ++i) {
    if((*i) == T) {
      condicion1 = true;
    }
  }

  for(long unsigned int i = 0; i < visitados.size(); ++i) {
    if(visitados[i] == T) {
      condicion2 = false;
    }
  }

  for(auto i = no_visitados.begin(); i != no_visitados.end(); ++i) {
    if((*i) == T) {
      condicion3 = true;
    }
  }
  return condicion1 && condicion2 && condicion3;
}

bool Find(std::set<std::set<Node>> estadosDFA, std::set<Node> H) {
  bool resultado = false;
  for(auto itr = estadosDFA.begin(); itr != estadosDFA.end(); ++itr) {
    if((*itr) == H) {
      resultado = true;
    }
  }
  return resultado;
}

void EscribirSet(std::ofstream& DFA_file, const std::set<Node>& set) {
  std::string texto;
  for(auto i = set.begin(); i != set.end(); ++i) {
    texto += std::to_string((*i).GetNode());
  }
  DFA_file << texto;
}

bool BuscarAceptacion(const std::set<Node>& set) {
  bool resultado = false;
  for(auto i = set.begin(); i != set.end(); ++i) {
    if((*i).GetType()) {
      resultado = true;
    }
  }
  return resultado;
}

void FiniteAutomaton::Escribir(std::ofstream& DFA_file, std::set<std::set<Node>>& estadosDFA, std::map<std::pair<std::set<Node>, Symbol>, std::set<Node>>& transDFA) {
  //Escribe el alfabeto del automata
  for(auto i = automaton_language_.Begin(); i !=automaton_language_.End(); ++i) {
    if(i != automaton_language_.End()--) {
    DFA_file << (*i) << " ";
    }
    else
      DFA_file << (*i);
  }
  DFA_file << std::endl;
  int contador = 0;
  //Escribe el numero de estados del automata
  for(auto i = estadosDFA.begin(); i != estadosDFA.end(); ++i) {
    contador++;
  }
  DFA_file << contador << std::endl;
  //Escribe el nodo de arranque
  DFA_file << start_node_.GetNode() << std::endl;
  for(auto itr = transDFA.begin(); itr != transDFA.end(); ++itr) {
    EscribirSet(DFA_file, itr->first.first);
    DFA_file << " ";
    DFA_file << BuscarAceptacion(itr->first.first);
    DFA_file << " ";
    int numero = 0;
    /*
    for(auto i = transDFA.begin(); i != transDFA.end(); ++i) {
      numero++;
    DFA_file << numero << " ";
    */
    for(auto itr = transDFA.begin(); itr != transDFA.end(); ++itr) {
      DFA_file << itr->first.second;
      DFA_file << " ";
      EscribirSet(DFA_file, itr->second);
      DFA_file << " ";
      //++itr;
  }
  DFA_file << std::endl;
  }
}

void FiniteAutomaton::ConstruccionSubconjuntos(std::ofstream& DFA_file) {
  std::vector<std::set<Node>> visitados; //marcados
  std::list<std::set<Node>> no_visitados; //desmarcados
  std::set<std::set<Node>> estadosDFA; //estadosDFA
  std::set<Node> estadoInicial; //q0
  std::map<std::pair<std::set<Node>, Symbol>, std::set<Node>> transDFA;
  estadoInicial.insert(start_node_);
  EpsilonClosure(estadoInicial);
  std::set<Node> T; //T
  T = estadoInicial;
  estadosDFA.insert(T);
  no_visitados.push_back(T);
  while(Condiciones(T, estadosDFA, visitados, no_visitados)) {
    std::set<Node> H; //H
    T = no_visitados.front();
    no_visitados.pop_front();
    visitados.push_back(T);
    for(auto i = automaton_language_.Begin(); i !=automaton_language_.End(); ++i) {
      H = T;
      Move(H, (*i));
      EpsilonClosure(H);
        if(Find(estadosDFA, H) == false) {
          no_visitados.push_back(H);
          estadosDFA.insert(H);
        }
        std::pair<std::set<Node>, Symbol> transicion (T, (*i));
        transDFA[transicion] = H;
    }
    T = H;
  }
  Escribir(DFA_file, estadosDFA, transDFA);
  for(auto itr = transDFA.begin(); itr != transDFA.end(); ++itr) {
    std::cout << "desde el estado :";
    PrintSet(itr->first.first);
    std::cout << " con el simbolo: " << itr->first.second << " al estado: ";
    PrintSet(itr->second);
    std::cout << std::endl; 
  }
}

void FiniteAutomaton::ShowAutomaton() {
  for (auto i = finite_automaton_.begin(); i != finite_automaton_.end(); ++i) {
    Transition transition(i->second);
    std::cout << (i->first).GetNode()<< " " << (i->first).GetType() << " " << transition.GetTransitionSymbol().GetChar() << " " << transition.GetTransition().GetNode() << std::endl;
  }
}
