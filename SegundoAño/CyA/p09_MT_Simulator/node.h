// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9:  Simulación de maquinas de Turing
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo estado.h: Archivo con la definicion de la clase estado.h
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

//Aseguro que el codigo fuente que lo invoca sea incluido una sola vez
#pragma once
#include <iostream>

class Node {

  public:

  //Constructor
  Node(void);
  Node(int identificator);
  Node(const Node& identificator);

  //Getter
  const int GetId(void) const;
  //Métodos

  //Operador < para usar sets
  bool operator<(const Node& node) const;
  friend std::ostream &operator<<(std::ostream &os, const Node& n);
  friend bool operator==(const Node& node1, const Node& node2);
  private:
  
    int identificator_; //nombre

};