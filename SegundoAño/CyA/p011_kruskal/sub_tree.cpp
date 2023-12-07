// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: EMST
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/12/2023
// Archivo sub_tree.cpp: archivo con la definicion de las funciones de la clase sub_tree.hpp
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 07/12/2023 - Creación del código

#include <iomanip>
#include <cmath>

#include <algorithm>
#include <utility>
#include "sub_tree.hpp"

namespace EMST {
    sub_tree::sub_tree(void) : arcs_(), points_(), cost_(0) {}

    sub_tree::~sub_tree(void) {
    }

    void sub_tree::add_arc(const CyA::arc &a) {
        arcs_.push_back(a);

        points_.insert(a.first);
        points_.insert(a.second);
    }

    void sub_tree::add_point(const CyA::point &p) {
        points_.insert(p);
    }

    bool sub_tree::contains(const CyA::point &p) const {
        return points_.find(p) != points_.end();
    }

    void sub_tree::merge(const sub_tree &st, const CyA::weigthed_arc &a) {
        arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
        arcs_.push_back(a.second);

        points_.insert(st.points_.begin(), st.points_.end());
        points_.insert(a.second.first);
        points_.insert(a.second.second);

        cost_ += a.first + st.get_cost();
    }
}