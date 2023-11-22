// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 5: Implementacios de un simulador de automatas finitos
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 19/09/2023
// Archivo cya-P05-automata-simulator
// Contiene la función main del proyecto.
// Para hacer un automata finito
// 17/09/2023 - Creación (primera versión) del código
#include<iostream>
#include<algorithm>
#include<iterator>
#include "cadena.h"
#include "automata.h"
/*
void Automata::Insertar_transicion(std::string nombre, char a) {
  multimap_transiciones_.insert(std::pair<std::string, char>(nombre, a));
}
*/
std::ostream &operator<<(std::ostream &os, Automata p) {
  os << "El numero de estados es: " << p.GetNumEstados() << std::endl;
  os << "El estado de arranque es: q" << p.GetArranque() << std::endl;
  for(auto itr = p.multimap_.begin(); itr != p.multimap_.end(); ++itr) {
    os << "estado: " << itr->first << " transicion: " << itr->second.GetEstadoInicial() << "\n";
  }
  return os;
}

std::set<Estado> Automata::ProcesarTransiciones(Estado &estado, char simbolo_actual) {
    //nodos a los que transita, uso un set ya que puede haber mas de un estado.
    std::set<Estado> siguiente_estado;

    //Recorremos las transiciones del estado especificado
    for (auto i = multimap_.lower_bound(estado); i != multimap_.upper_bound(estado); ++i) {
        Transicion transicion_actual(i -> second);
        //Si el simbolo de la cadena coincide con el simbolo de la transicion
        char simbolo_aux = simbolo_actual;
        //Cadena cadena_auxiliar(simbolo_aux);
        if ( transicion_actual.GetSimboloTransicion() == simbolo_actual && alfabeto_.EstaEnLenguaje(simbolo_aux)) {
            //Recorremos el automata para copiar el estado de transicion
            for(auto j = multimap_.begin(); j != multimap_.end(); ++j) {
                //creamos el estado siguiente
                Estado estado_aux(j->first);
                //Si el estado al que transita == estado en el automata
                if(estado_aux == transicion_actual.GetTransicion()) {
                    Estado nuevo_estado(transicion_actual.GetTransicion().Get_nombre(), estado_aux.Get_Aceptacion());
                    siguiente_estado.insert(nuevo_estado);
                }
            }
        }
    }
    
    
    return siguiente_estado;
}

bool Automata::EstaEnLenguaje(char simbolo) {
    bool resultado = false;
    for(auto itr = alfabeto_.GetAlfabeto().begin(); itr != alfabeto_.GetAlfabeto().end(); ++itr) {
      if(*itr == simbolo) {
        resultado = true;
      }
    }
  return resultado;
}

/*
bool Automata::Search_multimap(std::set<Estado>& estados, char a) {
  bool resultado = false;
  for(auto itr = multimap_.begin(); itr != multimap_.end(); itr++) {
      for(std::set<Estado>::iterator i = estados.begin(); i != estados.end(); i++) {
        resultado = (itr->first == *i && itr->second.Get_simbolo() == a); 
      }
  }
  return resultado;
}
*/
/*
std::set<Estado> Automata::Get_estado_destino(std::set<Estado>& estados, char a) {
  std::set<Estado> set;
  for(auto itr = multimap_.begin(); itr != multimap_.end(); ++itr) {
      for(std::set<Estado>::iterator i = estados.begin(); i != estados.end(); i++) {
        if(itr->first == (*i) && itr->second.Get_simbolo() == a) {
          set = itr->second.Get_estado();
        }
      }
  }
  return set;
}
*/
