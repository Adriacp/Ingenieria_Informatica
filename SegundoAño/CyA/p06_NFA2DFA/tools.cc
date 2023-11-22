// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo tools.cc: Archivo con la declaracion de las funciones usadas en el main.cc
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 24/09/2023 - Creación del código

#include<iostream>
#include "finite_automaton.h"

//Funcion Usage que muestra el modo de empleo del programa.
void Usage() {
    std::cout << "Modo de empleo: ./p06NFA2DFA input.fa input.txt output.dfa" << std::endl;
    std::cout << "Pruebe ./p06NFA2DFA --help para mas informacion" << std::endl;
}

//Funcion que muestra una ayuda sobre el programa (que hace cada opcode y la forma de pasar los parametros).
void Help() {
  std::cout << "El programa recive un fichero de entrada como primer parametro, este fichero tendrá la definición del automata\n"
               "Este primer fichero sigue la siguiente estructura:\n"
               "Línea 1: Símbolos del alfabeto separados por espacios.\n"
               "Línea 2: Número total de estados del automata\n"
               "Línea 3: Estado de arranque del automata\n"
               "A continuación figurará una línea para cada uno de los estados. Cada línea contendrá los siguientes números, separados entre sí por espacios en blanco:\n"
               "Número identificador del estado. Los estados del autómata se representarán mediante números naturales.\n" << "La numeración de los estados corresponderá a los primeros números comenzando en 0.\n"
               "Un 1 si se trata de un estado de aceptación y un 0 en caso contrario.\n"
               "Número de transiciones que posee el estado\n"
               "A continuación, para cada una de las transiciones, y utilizando espacios en blanco como separadores \n" << "se detallará la información siguiente:\n"
               "Símbolo de entrada necesario para que se produzca la transición. \n" << "Para representar la cadena vacía (el no consumir símbolo de la entrada) se utilizará el carácter &\n"
               "Estado destino de la transición.\n"
               "El programa transformara el NFA dado en un DFA y colocará su descripción en el archivo de texto output.dfa\n";
}

//Funcion para comprobar los parametros.
//Parametros: argc (numero de parametros), argv vector de punteros a cada parametro.
bool CheckParameters(int& argc, char* argv[]) {
  bool correct_parameters {true};
  //Si hay mas de 4 parametros, es incorrecto.
  if (argc > 4) {
    Usage();
    correct_parameters = false;
  }
  //Si hay 2 parametros y coincide con --help, mostramos la ayuda.
  if (argc < 4 && argc == 2) {
    std::string key_word{argv[1]};
    if (key_word == "--help") {
        Help();
        correct_parameters = false;
    }
  }
  //Si hay menos de 4 parametros y no hay 2, uso incorrecto.
  if (argc < 4 && argc != 2) {
    Usage();
    correct_parameters = false;
  }
  return correct_parameters;
}

//Comprobacion de apertura de fichero de entrada.
//Parametros: file (stream del fichero de entrada), file_name (nombre del fichero de entrada).
bool CheckInputFileOpening(std::ifstream& file, std::string file_name) {
  bool right_opening {true};
  //Abrimos el fichero en nuestro stream.
  file.open(file_name);
  //Si no abre, apertura incorrecta.
  if (!file) {
    std::cout << "Error al abrir el fichero de entrada" << std::endl;
    Usage();
    right_opening = false;
  }
  return right_opening;
}

void ResultEvaluation(std::ifstream& my_file,FiniteAutomaton& automaton) {
  std::string file_chain;
  while ( my_file >> file_chain) {
    Chain chain(file_chain);
    std::cout << chain << " --- ";
    if (automaton.EvaluateChain(chain) == true) {
        std::cout << "Accepted" << std::endl;
    } else {
        std::cout << "Rejected" << std::endl;
    }
  }
  my_file.close();
}