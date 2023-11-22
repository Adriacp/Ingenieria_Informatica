
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo language.cc: Archivo con la definicion de los metodos de la clase language
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 24/09/2023 - Creación del código

#include "language.h"

//Constructo vacio para poder crear nuestros lenguajes a partir de el.
Language::Language(void) {

}

//Metodo de insercion de cadenas al lenguaje.
//Parametros: chain (cadena a insertar).
void Language::Insert(Chain& chain) {
  language_.insert(chain);
  length_ += 1; //aumentamos el tamaño ya que por defecto esta vacio.
}

//Getter del tamaño del lenguaje.
const int Language::GetLenght() const {
  return length_;
}

//Getter de una cadena en el lenguaje.
//Parametros: itr (iterador que contiene la posicion de la cadena).
const Chain Language::GetChain(std::set<Chain>::iterator itr) {
    Chain chain(*itr); //*itr para acceder al contenido del iterador.
    return chain;
}

//Construye un alfabeto a partir de una cadena.
//Parametros: chain (cadena sobre la que construir el alfabeto).
void Language::MakeAlphabet(Chain& chain) {
  //Recorremos la cadena simbolo a simbolo e insertamos cada uno.
  //Gracias a la sobrecarga del operador < para chains, se ordenan y no se guardan dos cadenas iguales.
  for (int i = 0; i < chain.GetLenght(); ++i) {
    Symbol character(chain[i].GetChar());
    Chain symbol(character);
    language_.insert(symbol);
    length_++;
  }
}

//Getter del iterador con la posicion de inicio del lenguaje.
auto Language::Begin() const {
  auto itr = language_.begin();
  return itr;
}

//Getter del iterador con la posicion del final del leguaje.
auto Language::End() const {
  auto itr = language_.end();
  return itr; 
}

bool Language::IsInLanguage(Chain& chain) {
  bool in_language = false;
  for (auto i = language_.begin(); i != language_.end(); ++i) {
    Chain aux_chain(*i);
    if (chain == aux_chain) {
      in_language = true;
    }
  }
  return in_language;
}

//Sobrecarga del operador de salid para mostrar por pantalla.
//Parametros: output (stream de salida) , Language (lenguaje que queremos mostrar).
std::ostream& operator<<(std::ostream& output, Language& Language) {
  //abrimos el conjunto.
  output << "{ ";
  auto itr = Language.Begin();
  //Si es la primera cadena del lenguaje, la metemos al stream.
  if (itr != Language.End()) {
    output << Language.GetChain(itr);
    ++itr;
  }
  //Recorremos el resto del lenguaje hasta llegar al final, seperamos de la cadena inicial con "," e insertamos cadenas.
  while (itr != Language.End()) {
    output << ", " << Language.GetChain(itr);
    ++itr;
  }  
  //Cerramos el conjunto.
  output << " }";
  return output;
}