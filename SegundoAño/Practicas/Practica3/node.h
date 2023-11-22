// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo finite_automaton.cc: Archivo con la declaracion de la clase Node.
// Contiene la declaración de la clase Node
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 14/10/2023 - Creación del código

#ifndef NODE_H_
#define NODE_H_

class Node {

  public:
  
  //Constructores
  Node(void);
  Node(int node, bool type);
  Node(const Node& node);

  //Getters
  const int GetNode() const;
  const bool GetType() const;
  
  //Operador < para usar sets
  bool operator<(const Node& node) const;

  private:

  int node_;  // Nombre
  bool type_;  // true (acceptance) / false (not acceptrance)

};

#endif //NODE_H_