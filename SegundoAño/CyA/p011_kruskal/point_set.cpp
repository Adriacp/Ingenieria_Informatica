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

point_set::point_set(const CyA::point_vector &points) {
    //definicion constructor
}

void point_set::EMST(void) {
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
    //definicion write_tree
}

void point_set::write(std::ostream &os) const {
    //definicion write
}

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

    void point_set::find_incident_subtrees(const forest &st, const CyA::arc &a, int &i, int &j) const {
        i = j = -1;  // Inicializar índices con un valor no válido

      for (int index = 0; index < st.size(); ++index) {
        const EMST::sub_tree &subtree = st[index];

        // Comprobar si los extremos del arco están en el mismo subárbol
        if (subtree.contains(a.first) || subtree.contains(a.second)) {
          if (i == -1) {
              i = index;
          } else {
              j = index;
              break;  // Se encontraron ambos subárboles, salir del bucle
          }
        }
      }
    }

    void point_set::merge_subtrees(forest &st, const CyA::arc &a, int i, int j) const {
        //Verifico si los indices son válidos
        if (i < 0 || i >= st.size() || j < 0 || j >= st.size()) {
         std::cerr << "Error en los indices al fusionar\n";
         exit(EXIT_FAILURE);
        }
        // Fusionar los subárboles en st[index_i] y st[index_j]
        st[i].merge(st[j], a);

        // Eliminamos el subárbol fusionado de st
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
