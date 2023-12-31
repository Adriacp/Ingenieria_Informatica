// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: EMST
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/12/2023
// Archivo point_set.cpp: archivo con la definicion de las funciones de la clase point_set.hpp
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 07/12/2023 - Creación del código

#include <iostream>
#include <algorithm>

#include "point_set.hpp"
#include "point_types.hpp"
#include "sub_tree.hpp"
#include "point_set.h"

point_set::point_set(const CyA::point_vector &points) {
  emst_.clear();
}

/// @brief Funcion que genera el árbol generador mínimo euclidiano 
/// @param  void
void point_set::EMST(void) {
  /*
  if (this->empty()) {
    // Manejar el caso en el que el vector de puntos está vacío
    std::cerr << "Error, vector vacio\n";
    exit(EXIT_SUCCESS);
  }
  */
  
  CyA::arc_vector av;
  compute_arc_vector(av);

  forest st;

  for (const CyA::point &p : *this) {
    EMST::sub_tree s;
    s.add_point(p);

    st.push_back(s);
  }

  for (const CyA::weigthed_arc &a : av) {
    int i, j;
    find_incident_subtrees(st, a.second, i, j);
    
    if (i != j) {
      merge_subtrees(st, a.second, i, j);
    }
    
  }

  emst_ = st[0].get_arcs();
}

void point_set::write_tree(std::ostream &os) const {
    for (const auto &arc : emst_) {
        os << "(" << arc.first.first << ", " << arc.first.second << ") -> (" 
           << arc.second.first << ", " << arc.second.second << ")\n";
    }

    os << compute_cost() << std::endl;
}

void point_set::write(std::ostream &os) const {
    //definicion write
}

/// @brief Calcula el coste de los arcos del arbol
/// @param av vector con los arcos
void point_set::compute_arc_vector(CyA::arc_vector &av) const {
  av.clear();
 
  const int n = size();
 
  for (int i = 0; i < n - 1; ++i) {
    const CyA::point &p_i = (*this)[i];
    for (int j = i + 1; j < n; ++j) {
      const CyA::point &p_j = (*this)[j];
 
      const double dist = euclidean_distance(std::make_pair(p_i, p_j));

      av.push_back(std::make_pair(dist, std::make_pair(p_i, p_j)));
    }
  }
 
  std::sort(av.begin(), av.end());
}

/// @brief Calcula los subarboles incidentes
/// @param st bosque de subarboles
/// @param a arco
/// @param i indice
/// @param j indice
void point_set::find_incident_subtrees(const forest &st, const CyA::arc &a, int &i, int &j) const {
  for(int k = 0; k < st.size(); k++) {
    if(st[k].contains(a.first)) {
      i = k;
    }
    else if(st[k].contains(a.second)) {

      j = k;
    }
  }
}

/// @brief Funcion que fusiona los subarboles en caso de ser incidentes
/// @param st bosque
/// @param a arco
/// @param i indice
/// @param j indice
void point_set::merge_subtrees(forest &st, const CyA::arc &a, int i, int j) const {
  CyA::weigthed_arc enlace {euclidean_distance(a), a};
  st[i].merge(st[j], enlace);
  st.erase(st.begin() + j);
}

double point_set::compute_cost(void) const {
  //definicion compute_cost
  return 0.0;
}

double point_set::euclidean_distance(const CyA::arc &a) const {
  //definicion euclidean_distance
  return 0.0;
}
