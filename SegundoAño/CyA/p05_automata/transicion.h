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
#ifndef TRANSICION_H_
#define TRANSICION_H_
#include "estado.h"
#include<set>

class Transicion {

public:

  //Constructores
  Transicion(char estado_inicial, bool tipo_estado1, char simbolo, int estado_final, bool tipo_de_estdo_final);
  Transicion(Estado &estado, char simbolo, Estado &estado_final);
  Transicion(const Transicion &transicion);

  //Getters
  const Estado GetTransicion() const;
  const char GetSimboloTransicion() const;
  const Estado GetEstadoInicial() const;

  //Métodos
  void print();
private:

  Estado estado_inicial_;
  char simbolo_;
  Estado estado_final_;

};

#endif //TRANSICION_H_