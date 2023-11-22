// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con cadenas
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 23/09/2023
// Archivo chain.c: Archivo con la definicion de los metodos de la clase chain
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 23/09/2023 - Creación del código
// 24/09/2023 - Correción del formato de datos a vector<Symbol>

#include "chain.h"
#include <iostream>


//Constructor pasado un string.
//Parametros: string (contiene la cadena que queremos crear).
Chain::Chain(std::string chain) {
  //Si no es una cadena vacia.
  if (chain.size() > 0) {
    chain_.resize(chain.size()); //Establecemos el tamaño del chain.
    //Recorremos el string y creamos simbolos a partir de cada literal para insertar a nuestro chain.
    for (long unsigned int i = 0; i < chain.size(); i++) {
      Symbol symbol(chain[i]);
      chain_[i] = symbol;
    }
  }
  //Si la cadena es vacia.
  if (chain.size() == 0) {
    chain_.resize(1); //Tamaño 1 (simbolo '&?)).
    Symbol empty('&');// '&' representa la cadena vacia.
    chain_[0] = empty;
  }
}

//Constructor de copia.
//Parametros: chain (cadena que queremos copiar).
Chain::Chain(const Chain& chain) {
  chain_.resize(chain.GetLenght()); //Redimensionamos el tamaño.
  //Recorremos cada simbolo de chain y lo copiamos.
  for (int i = 0; i < chain.GetLenght(); i++) {
    chain_[i] = chain[i];
  }
}

//Constructor para cadenas de un solo simbolo.
//Parametros: symbol (simbolo para crear la cadena).
Chain::Chain(Symbol& symbol) {
  chain_.resize(1);
  chain_[0] = symbol;
}

//constructor por defecto.
Chain::Chain() {
  chain_.resize(1);
  Symbol empty('&');
  chain_[0] = empty;
}

//Getter de length (tamaño del chain).
const int Chain::GetLenght() const {
  return chain_.size();
}

//Getter de un simbolo de la cadena, no se puede modificar los valores de la posicion.
//Parametros: espace (indice de la posicion del simbolo en cadena).
const Symbol& Chain::at(const int espace) const{
  return chain_[espace];
}

//Sobrecarga operador de indexacion, no permite modificar los valores de la posicion.
//Parametros: espace (indice de la posicion del simbolo en cadena).
const Symbol& Chain::operator[](const int espace) const{
  return at(espace);
}

//Parecido al at anterior pero permite cambiar el valor en esa posicion.
//Parametros: espace (indice de la posicion del simbolo en cadena).
Symbol& Chain::at(const int espace) {
  return chain_[espace];
}

//Sobrecarga operador de indexacion que permite modificar lo que hay en la posicion.
//Parametros: espace (indice de la posicion del simbolo en cadena).
Symbol& Chain::operator[](const int espace) {
  return at(espace);
}

//Sobrecargo operador de salida para hacer cout de un chain.
//Parametros: output (flujo de salida) , chain (cadena para mostrar en pantalla). 
std::ostream& operator<<(std::ostream& output, const Chain& chain) {
  //recorremos la chain e insertamos simbolo por simbolo.
  for (int i = 0; i < chain.GetLenght(); i++) {
    output << chain[i].GetChar();
  }
  return output;
}

//Operador de ordenacion para los set de la clase Language.
//Parametros: chain (cadena que insertamos).
bool Chain::operator<(const Chain& chain) const {
  bool smaller = false;
  //Si tiene mayor longitud.
  if (chain.GetLenght() > chain_.size()) {
    smaller = true;
  }
  //Si tienen igual longitud, recorremos las chains y comparamos simbolo por simbolo.
  if (chain.GetLenght() == chain_.size()) {
    for (int i= 0; i < chain.GetLenght(); ++i) {
      if (chain[i].GetChar() > chain_[i].GetChar()) {
        smaller = true;
      }
    }
  }
  return smaller;
}


//Metodo para obtener la cadena inversa de otra cadena.
//Parametros: chain (cadena a invertir).
void Chain::InverseChain(Chain& chain) {
  chain_.resize(chain.GetLenght()); //Aseguramos que tengan mismo tamaño.
  //Recorremos la cadena a invertir desde el final y las guardamos desde el inicio.
  for (int i = 0; i < chain.GetLenght(); i++) {
    chain_[i] = chain[(chain.GetLenght() - 1) - i];
  }
}

//Metodo para redimensionar nuestra chain.
void Chain::Resize(int length) {
  chain_.resize(length);
}

bool Chain::operator==(Chain& chain) {
 bool equal = true;
 if (chain.GetLenght() != chain_.size()) {
  equal = false;
 }
 for (long unsigned int i = 0; i < chain_.size(); ++i) {
  if (chain[i].GetChar() != chain_[i].GetChar()) {
    equal = false;
  }
 }
  return equal;
}

//Metodo para obtener un prefijo dado un tamaño.
//Parametros: length (tamaño del prefijo que queremos obtener).
Chain Chain::ChainPrefix(int length) {
  //Por defecto inciamos el prefijo como cadena vacia, ya que esta es prefijo de toda cadena.
  Chain Prefix("");
  //Si queremos una distancia mayor.
  if (length > 0) {
    Prefix.Resize(length); //Redimensionamos.
    //Recorremos guardando cada simbolo ordenado para formar el prefijo.
    for(int i= 0; i <= length; ++i) {
      Prefix[i] = chain_[i];
    }
  }
  return Prefix;
}

//Metodo para obtener un sufijo dado un tamaño.
//Parametros: length (tamaño del sufijo que queremos obtener).
Chain Chain::ChainSufix(int length) {
  //Por defecto inciamos el sufijo como cadena vacia, ya que esta es prefijo de toda cadena.
  Chain Sufix("");
  //Si queremos una distancia mayor.
  if (length > 0) {
    Sufix.Resize(length); //Redimensionamos.
    //Recorremos desde el tamaño que queremos hasta el final de la cadena, guardandolos en orden.
    for (int i = 0; i < length; ++i) {
      Sufix[i] = chain_[(chain_.size() - 1) -length + i + 1];
    }
  }
  return Sufix;
}