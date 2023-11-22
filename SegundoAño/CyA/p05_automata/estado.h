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
#ifndef ESTADO_H_
#define ESTADO_H_
#include<vector>
#include<map>
#include<iostream>
class Estado {

public:

  //Constructores
  Estado(char nombre, bool aceptacion, int numero_transiciones, std::vector<char> transiciones);
  Estado(char nombre) {nombre_ = nombre;}
  Estado(char nombre, bool aceptacion) {nombre_ = nombre; aceptacion_ = aceptacion;}
  Estado(){}

  //Setters
  void Set_aceptacion(char num) {aceptacion_ = num;}
  void Set_nombre(char nombre) {nombre_ = nombre;}
  void Set_numero_transiciones(int num) {numero_transiciones_ = num;}

  //Getters
  bool Get_Aceptacion() const {return aceptacion_;}
  int Get_numero_transiciones(){return numero_transiciones_;}
  char Get_nombre() const {return nombre_;}

  //Sobrecargas
  bool operator<(Estado const &e) const;
  bool operator==(Estado p) const;
  friend std::ostream &operator<<(std::ostream &os, Estado p);

private:

  char nombre_;
  bool aceptacion_;
  int numero_transiciones_;

};

#endif //ESTADO_H_