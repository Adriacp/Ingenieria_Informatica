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
#ifndef ALFABETO_H_
#define ALFABETO_H_
#include<set>

class Alfabeto{
  public:

  //Constructores
  Alfabeto(std::set<char>& alfabeto) {alfabeto_ = alfabeto;}
  Alfabeto(void) {}

  //Métodos
  std::set<char>::iterator Begin();
  std::set<char>::iterator End();
  void Insertar_simbolo(char& caracter) {alfabeto_.insert(caracter);}
  void Imprimir_alfabeto(void);
  bool Comprobar_simbolo(char);
  bool EstaEnLenguaje(char simbolo);

  //Getters
  std::set<char> GetAlfabeto(){return alfabeto_;}

  //Sobrecargar
  void operator=(Alfabeto& alfabeto);
  
  private:

  std::set<char> alfabeto_;
};

#endif //ALFABETO_H_