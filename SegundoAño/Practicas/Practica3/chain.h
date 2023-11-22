
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo chain.h: Archivo con la declaracion de la clase chain
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 23/09/2023 - Creación del código
// 24/09/2023 - Correción del formato de datos a vector<Symbol>

#ifndef CHAIN_H_
#define CHAIN_H_

#include <iostream>
#include <vector>
#include "symbol.cc"

class Chain {
  
  public:

  //Constructores.
  Chain(std::string chain);
  Chain(const Chain& chain); //Constructor de copia
  Chain(Symbol& symbol);
  Chain();

  //Getter del tamaño del vector.
  const int GetLenght() const;

  //Redimensionamiento del vector.
  void Resize(int length);

  //Sobrecarga de operador [], para poder acceder mas facil a los datos.
  //Esta sobrecarga permite obtener los datos almacenados pero no modificarlos.
  const Symbol& at(const int espace) const;
  const Symbol& operator[](const int espace) const;
  
  //Sobrecarga de operador [], para poder acceder mas facil a los datos
  //Esta sobrecarga permite insertar o cambiar valores.
  Symbol& at(const int espace);
  Symbol& operator[](const int espace);

  bool operator==(Chain& chain);

  //Metedo que crea una cadena inversa.
  void InverseChain(Chain& chain);

  //Metodos para obetener cadenas con subfijos y prefijos de otra cadena.
  Chain ChainPrefix(int length);
  Chain ChainSufix(int length);

  //Sobrecarga operador < para ordenacion por tamaño y orden alfabetico.
  //Se usará en la clase Language para poder meter las chains en el set.
  bool operator<(const Chain& chain) const; 

  //Sobrecarga del operador de salida para hacer cout.
  friend std::ostream& operator<<(std::ostream& output, const Chain& chain);

  private:
  std::vector<Symbol> chain_; //Las chains son vectores de symbols.
  
};

#endif //CHAIN_H_