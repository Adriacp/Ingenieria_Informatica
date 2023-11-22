// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo symbol.h: Archivo con la declaracion de la clase symbol.
// Contiene la declaración de la clase symbol
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 23/09/2023 - Creación del código

#ifndef SYMBOL_H_
#define SYMBOL_H_

class Symbol {

  public:

  //Constructor
  Symbol(char symbol = ' ');
  Symbol(std::string& symbol);
  //Getter de symbol_
  const char GetChar() const;

  private:

  char symbol_;  // Caracter que guarda symbol

};

#endif //SYMBOL_H_