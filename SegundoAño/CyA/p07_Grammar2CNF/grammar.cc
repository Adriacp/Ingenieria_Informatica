// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 27/10/2023
// Archivo grammar.cc: Archivo con la definicion de los metodos de la clase grammar.cc
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

#include "grammar.h"
#include <iterator>
#include <algorithm>
#include <fstream>
#include <string>

/// @brief Constructor de la clase grammar.h que lee un archivo de entrada con la definición
/// @param input_file archivo de entrada desde el que lee la definicion de la gramática
Grammar::Grammar(std::ifstream& input_file) {
  int terminals_num, nonterminals_num, productions_num;
  std::string line;
  getline(input_file, line);
  terminals_num = std::stoi(line);
  for(int i = 0; i < terminals_num; i++) { //recorro cada linea y guardo los terminales en el Alphabet
    getline(input_file, line);
    Symbol symbol = line[0];
    terminals_.insert(symbol);
  }
  getline(input_file, line);
  nonterminals_num = std::stoi(line);
  for(int i = 0; i < nonterminals_num; i++) { //recorro cada linea y la guardo los no terminales en el Alphabet
    getline(input_file, line);
    if(i == 0) initial_ = line[0];
    Symbol symbol = line[0];
    nonterminals_.insert(symbol);
  }
  getline(input_file, line);
  productions_num = std::stoi(line);
  for(int i = 0; i < productions_num; i++) { //recorro cada linea y lo guardo en las producciones
    getline(input_file, line);
    Symbol nonTerminal, vectorSymbol;
    std::vector<Symbol> vectorOfSymbols;
    nonTerminal = line[0];
    if(nonterminals_.find(nonTerminal)) {
      for(long unsigned int j = 2; j < line.size(); j++) {
        vectorSymbol = line[j];
        vectorOfSymbols.emplace_back(vectorSymbol);
      }
      productions_.emplace(nonTerminal, vectorOfSymbols); //Guardo la producción en el multimap
    }
  }
}

/// @brief Método de la clase grammar que busca si el symbol dado está dentro del alphabeto nonterminals
/// @param nonTerminal symbolo a buscar
/// @return devuelve el booleano qeu acredita si estaba o no
bool Grammar::Find(Symbol &nonTerminal) {
  bool resultado;
  resultado = nonterminals_.find(nonTerminal);
  return resultado;
}

/// @brief Genera un no terminal para cambiarlo a forma normal de chomsky
/// @return devuelve el Symbol nonTerminal nuevo
Symbol Grammar::GenerateNewNonTerminal() {
  int ascii = 84;
  Symbol nonTerminal = static_cast<char>(ascii);
  while(nonterminals_.find(nonTerminal)) {
    ascii++;
    nonTerminal = static_cast<char>(ascii);
  }
  nonterminals_.insert(nonTerminal);
  return nonTerminal;
}

/// @brief Método que genera el algoritmo para transformar a la forma normal de chomsky
void Grammar::CNF() {
  CheckSingleProductions();
  //Primera parte del algoritmo
  for(std::set<Symbol>::iterator itr = nonterminals_.begin(); itr != nonterminals_.end(); ++itr) {
    std::multimap<Symbol, std::vector<Symbol>>::iterator it, itlow, itup;
    itlow = productions_.lower_bound(*itr);
    itup = productions_.upper_bound(*itr);

    for(it = itlow; it != itup; ++it) {
      if(it->second.size() >= 2) {
        for(long unsigned int i = 0; i < it->second.size(); ++i) {
          if(terminals_.find(it->second[i])) {
            Symbol new_production = toupper(it->second[i].GetSymbol());
            std::vector<Symbol> new_vector;
            new_vector.emplace_back(it->second[i]);
            if(productions_.count(new_production) == 0) {
              productions_.emplace(new_production, new_vector);
              nonterminals_.insert(new_production);
            }
            it->second[i] = new_production;
          }
        }
      }
    }
  }
  //Segunda parte del codigo
  for(std::set<Symbol>::iterator itr = nonterminals_.begin(); itr != nonterminals_.end(); ++itr) {
    std::multimap<Symbol, std::vector<Symbol>>::iterator it, itlow, itup;
    itlow = productions_.lower_bound(*itr);
    itup = productions_.upper_bound(*itr);

    for(it = itlow; it != itup; ++it) {
      if(it->second.size() >= 3) {
        Symbol new_symbol = GenerateNewNonTerminal();
        std::vector<Symbol> new_vector;
        for(long unsigned int i = it->second.size(); i >1; i--) {
          new_vector.emplace(new_vector.begin(), it->second.back());
          it->second.pop_back();
        }
        it->second.emplace_back(new_symbol);
        productions_.emplace(new_symbol, new_vector);
      }
    }
  }
}

/// @brief comprueba si la gramática tiene producciones unitarias
void Grammar::CheckSingleProductions(void) {

  for(auto itr = productions_.begin(); itr != productions_.end(); ++itr) {
    if(productions_.count(itr->first) == 1 && itr->second.size() == 1 && nonterminals_.find(itr->second[0])) { //si el vector de producciones es de tamaño 1, es decir tiene una produccion y ademas esta en nonterminals, es unitario
      std::cerr << "No se puede transformar a la forma normal de Chosmky ya que posee producciones unitarias o vacias\n";
      exit(EXIT_FAILURE);
    }
  }
}

/// @brief Funcion para imprimir o mandar a fichero la gramática
/// @param os para poder usarlo para un fichero
void Grammar::Print(std::ostream& os) {
  os << terminals_.GetSize() << std::endl;
  os << terminals_;
  os << nonterminals_.GetSize() << std::endl;
  os << nonterminals_;
  //os << productions_.size() << std::endl;
  os << productions_.size() << std::endl;
  for(auto itr = productions_.begin(); itr != productions_.end(); itr++) {
    os << itr->first.GetSymbol() << " --> ";
    for(long unsigned int i = 0; i < itr->second.size(); i++) {
      os << itr->second[i].GetSymbol();
    }
    os << std::endl;
  }
}

//Sobrecarga del operador ==
const bool operator==(const Symbol& a, const Symbol& b) {
  return a.GetSymbol() == b.GetSymbol();
}


std::ostream &operator<<(std::ostream& os, Grammar& grammar) {
  grammar.Print(os);
  return os;
}

/// @brief Getter del alphabet terminals de la clase
/// @return devuelve el atributo alphabet terminals_ de la clase
const Alphabet Grammar::GetTerminals() const {
  return terminals_;
}

/// @brief Getter del alphabet nonterminals de la clase
/// @return devuelve el atributo alphabet nonterminals_ de la clase
const Alphabet Grammar::GetNonTerminals() const {
  return nonterminals_;
}

/// @brief Getter del simbolo no terminal de arranque
/// @return devuelve el atributo initial_ de la clase
const Symbol Grammar::GetInitial() const {
  return initial_;
}

/// @brief Getter del multimap que contiene las producciones de cada simbolo nonterminal_
/// @return devuelve el atributo multimap production_
const std::multimap<Symbol, std::vector<Symbol>> Grammar::GetProductions() const {
  return productions_;
}

