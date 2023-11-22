#include "subconjunto.h"

/// @brief Constructor por parámetros de subconjunto
/// @param name nombre del subconjunto
/// @param subconjunto set de estados que tiene el subconjunto
Subconjunto::Subconjunto(int name, std::set<Node> subconjunto) {
  name_ = name;
  subconjunto_ = subconjunto;
  SetAceptance();
}

Subconjunto::Subconjunto(int name) {
  name_=name;
}

/// @brief Constructor de copia de la clase
/// @param subconjunto objeto de la clase
Subconjunto::Subconjunto(Subconjunto &subconjunto) {
  name_ = subconjunto.GetName();
  subconjunto_ = subconjunto.GetSubconjunto();
  aceptance_ = subconjunto.GetAceptance();
}

/// @brief Getter que devuelve el atributo name_ de la clase
/// @return name_ atributo de la clase
const int Subconjunto::GetName() const {
  return name_;
}

/// @brief Getter que devuelve el atributo subconjunto_ de la clase
/// @return subconjunto_ atributo de la clase
const std::set<Node> Subconjunto::GetSubconjunto() const {
  return subconjunto_;
}

/// @brief Getter que devuelve el atributo aceptance_ de la clase
/// @return aceptance_ atributo de la clase
const bool Subconjunto::GetAceptance() const {
  return aceptance_;
}

/// @brief Define si el set de nodos es aceptado o no
void Subconjunto::SetAceptance() {
  aceptance_ = false;
  for(auto itr = subconjunto_.begin(); itr != subconjunto_.end(); ++itr) { //Recorre el set para comprobar si alguno de los estados es aceptado
    if((*itr).GetType() == true)
      aceptance_ = true;
  }
}

void Subconjunto::SetName(int a) {
  name_ = a;
}

void Subconjunto::SetSubconjunto(std::set<Node>& s) {
  subconjunto_ = s;
}

void Subconjunto::Construir(int a, std::set<Node>& s){
  name_ = a;
  subconjunto_ = s;
  SetAceptance();
}

void Subconjunto::Insert(Node& n) {
  subconjunto_.insert(n);
}

std::ostream &operator<<(std::ostream &os, const Subconjunto a) {
  for(auto itr = a.GetSubconjunto().begin(); itr != a.GetSubconjunto().end(); ++itr) {
    if(itr != a.GetSubconjunto().end()--) {
      os << (*itr) << " ";
    }
    else
      os << (*itr);
    return os;
  }
}