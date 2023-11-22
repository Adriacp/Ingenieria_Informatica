// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo language.h: Archivo con la declaracion de la clase language
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 24/09/2023 - Creación del código

#ifndef LANGUAGE_H_
#define LANGUAJE_H_

#include "chain.cc"
#include "symbol.h"
#include <set>

class Language {

  public:

  //Constructor
  Language(void);

  //Metodo para insertar cadenas al lenguaje.
  void Insert(Symbol& symbol);

  //Getters del tamaño y cadenas que forman el lenguaje.
  const int GetLenght() const;
  //const Chain GetChain(std::set<Chain>::iterator itr);
  const Symbol GetSymbol(std::set<Symbol>::iterator itr);

  //Getters de los iteradores que indican el inicio y final del set.
  auto Begin() const;
  auto End() const;

  //Metodo para crear el alfabeto (Lenguaje de cadenas de un solo simbolo) de un cadena.
  void MakeAlphabet(Chain& chain);
  bool IsInLanguage(Symbol& symbol);

  //Sobrecarga operador de salida para mostrar por pantalla.
  friend std::ostream& operator<<(std::ostream& output, Language& Language);

  private:

  std::set<Symbol> language_; //lenguaje es un set de chains.
  int length_ = 0; // Variable con el tamaño del lenguaje.
};

#endif //LANGUAGE_H_