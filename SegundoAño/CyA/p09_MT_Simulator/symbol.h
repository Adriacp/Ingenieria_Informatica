// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramática a forma normal de chomsky
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo symbol.h: Archivo con la definicion de la clase symbol.h
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

//Aseguro que el codigo fuente que lo invoca sea incluido una sola vez
#pragma once

#include <iostream>
#include <string>

class Symbol {

  //Metódos publicos de la clase Symbol
  public:

    //Constructor
    Symbol(char symbol = ' ');
    Symbol(std::string& symbol);
    Symbol(const Symbol& symbol);
    Symbol(const std::string& symbol);
    
    //Getter de symbol
    const char GetSymbol() const;

    //Sobrecarga
    bool operator<(const Symbol& symbol) const;
    void operator=(Symbol);
    void operator=(char);

    friend std::ostream &operator<<(std::ostream &os, const Symbol& a);
    friend bool operator==(Symbol &s1, Symbol &s2);
    friend bool operator==(Symbol &s, char a);

  //Atributos privados de la clase Symbol
  private:

  char symbol_;

};