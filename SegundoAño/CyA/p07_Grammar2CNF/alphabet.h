// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 27/10/2023
// Archivo alphabet.h: Archivo con la definicion de la clase alphabet.h
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

//Aseguro que el codigo fuente que lo invoca sea incluido una sola vez
#pragma once

#include "symbol.h"
#include <set>

class Alphabet {

  //Métodos publicos de la clase Alphabet
  public:

    //Constructores
    Alphabet(void) {}
    Alphabet(const Alphabet &a);

    //Getters
    const std::set<Symbol> GetAlphabet(void) const;
    const int GetSize(void) const;

    //Métodos
    void insert(Symbol&);
    bool find(Symbol&);
    std::set<Symbol>::iterator begin(void);
    std::set<Symbol>::iterator end(void);

    friend std::ostream& operator<<(std::ostream& os, const Alphabet alphabet);

  //Atributos privados de la clase Alphabet
  private:

    std::set<Symbol> alphabet_;
    int size_;
};