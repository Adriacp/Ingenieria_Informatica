// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 27/10/2023
// Archivo grammar.h: Archivo con la definicion de la clase grammar.h
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

//Aseguro que el codigo fuente que lo invoca sea incluido una sola vez
#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "symbol.h"
#include "alphabet.h"

//Clase gramática para manejar gramáticas independientes del contexto
class Grammar {
  
  //Métodos públicos de la clase Grammar
  public:
    //Constructores
    Grammar(std::ifstream& input_file);    

    //Getters
    const Alphabet GetTerminals(void) const;
    const Alphabet GetNonTerminals(void) const;
    const Symbol GetInitial(void) const;
    const std::multimap<Symbol, std::vector<Symbol>> GetProductions(void) const;

    //Métodos
    //Interseccion terminal y no terminal
    //Insertar producciones
    bool Find(Symbol&);
    void CNF(void);
    void Print(std::ostream&);
    void CheckSingleProductions(void);
    Symbol GenerateNewNonTerminal(void);

    friend std::ostream& operator<<(std::ostream&, Grammar&);

  //Atributos privados de la clase Grammar
  private:

    Alphabet terminals_; //Terminales intersección no terminales tiene que ser vacio
    Alphabet nonterminals_; // No terminales
    Symbol initial_; //Primer no terminal de la gramatica
    std::multimap<Symbol, std::vector<Symbol>> productions_; //Multimap de producciones

};