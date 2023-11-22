
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo finite_automaton.cc: Archivo con la función principal.
// Contiene el funcionamiento de la simulación de un automata
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#include "finite_automaton.cc"
#include "tools.cc"

int main(int argc, char* argv[]) {
  if (CheckParameters(argc,argv)) {
    std::ifstream automaton_file;
    std::string file_name{argv[1]};
    if (CheckInputFileOpening(automaton_file,file_name)) {
      FiniteAutomaton automaton(automaton_file);
      std::ifstream chain_file;
      std::string chain_input{argv[2]};
      if (CheckInputFileOpening(chain_file,chain_input)) {
        //automaton.ShowLanguage();
        //automaton.ShowNodeNumber();
        //automaton.ShowStartNode();
        //automaton.ShowAutomaton();
        ResultEvaluation(chain_file,automaton);
      }
      
    }
  }
return 0;
}