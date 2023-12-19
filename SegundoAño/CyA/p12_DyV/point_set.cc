// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: EMST
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/12/2023
// Archivo EMSTmain.cpp: Archivo principal
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 07/12/2023 - Creación del código

#include <iomanip>
#include <cmath>

#include "point_set.h"

#define MAX_SZ 3
#define MAX_PREC 0

    /// @brief Constructor de un point_set
    /// @param points vector de puntos
    CyA::point_set::point_set(const std::vector<point> &points) {
        hull_.clear();
        input_ = points;
    }

    /// @brief funcion que inicializa el algoritmo divide y venceras quickhull
    /// @param  void
    void CyA::point_set::quickHull(void) {
        hull_.clear();

        CyA::point min_x_point; 
        CyA::point max_x_point;

        x_bounds(min_x_point, max_x_point);
        //std::cout << min_x_point.first << ", " << min_x_point.second << " " << max_x_point.first << " " << max_x_point.second << "\n";

        quickHull(CyA::line(min_x_point, max_x_point), side::LEFT);
        quickHull(CyA::line(min_x_point, max_x_point), side::RIGHT);

        // Remove duplicates
        std::sort(hull_.begin(), hull_.end());
        hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
    }
     
    /// @brief funcion recursiva con el algoritmo divide y venceras quickhull
    /// @param l linea
    /// @param side lado
    void CyA::point_set::quickHull(const CyA::line &l, int side) {
        CyA::point farthest;

        if (farthest_point(l, side, farthest)) {
            quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
            quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
        } else {
            hull_.push_back(l.first);
            hull_.push_back(l.second);
        }
    }

    /// @brief funcion que calcula el punto mas lejano a una linea dada
    /// @param l linea
    /// @param side lado
    /// @param farthest puto
    /// @return punto mas lejano
    bool CyA::point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const {
        
        farthest = input_.at(0);

        double max_dist = 0;

        bool found = false;

        for (const CyA::point &p : input_)
        {
            const double dist = distance(l, p);

            if (find_side(l, p) == side && dist > max_dist)
            {
                farthest = p;
                max_dist = dist;
                found = true;
            }
        }

        return found;
    }

    /// @brief funcion que devuelve la distancia entra una linea y un punto
    /// @param l linea
    /// @param p punto
    /// @return distancia
    double CyA::point_set::point_2_line(const CyA::line &l, const CyA::point &p) const {
        const CyA::point &p1 = l.first;
        const CyA::point &p2 = l.second;

        return (p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first);
    }
    /// @brief funcion que calcula la distancia entre un punto y una linea
    /// @param l linea
    /// @param p punto
    /// @return distancia
    double CyA::point_set::distance(const CyA::line &l, const CyA::point &p) const {
        return fabs(point_2_line(l, p));
    }

    /// @brief funcion que calcula la distancia entre dos puntos
    /// @param p0 punto1
    /// @param p1 punto2
    /// @return distancia
    double CyA::point_set::distance(const point &p0, const point &p1) const {
      return std::sqrt(std::pow(p1.first - p0.first, 2) + std::pow(p1.second - p0.second, 2));
    }

    /// @brief funcion que busca los dos puntos mas lejanos entre si
    /// @param min_x punto mas alejado
    /// @param max_x el otro punto
    void CyA::point_set::x_bounds(CyA::point &min_x, CyA::point &max_x) const {
        min_x = input_[0];
        max_x = input_[0];

        for (auto i = 0; i < input_.size(); ++i) {
            if (input_[i].first < min_x.first) {
                min_x = input_[i];
            }
            if (input_[i].first > max_x.first) {
                max_x = input_[i];
            }
        }
}
    /// @brief funcion que identifica el lado en el que nos encontramos
    /// @param l linea
    /// @param p punto
    /// @return lado
    int CyA::point_set::find_side(const line &l, const point &p) const {
        int val = (p.second - l.first.second) * (l.second.first - l.first.first) -
                (l.second.second - l.first.second) * (p.first - l.first.first);
        if (val > 0) return 1;
        if (val < 0) return -1;
        return 0;
    }

    /// @brief funcion que escribe el vector con los puntos finales
    /// @param os salida
    void CyA::point_set::write_hull(std::ostream &os) const {
        for(int i = 0; i < hull_.size(); i++) {
            os << "(" << (hull_[i]).first << ", "
                << (hull_[i]).second << ") \n";
        }
    }

    void CyA::point_set::xbounds_hull() {
        CyA::point min_x, max_x;
        min_x = hull_[0];
        max_x = hull_[0];

        for (auto i = 0; i < hull_.size(); ++i) {
            if (hull_[i].first < min_x.first) {
                min_x = hull_[i];
            }
            if (hull_[i].first > max_x.first) {
                max_x = hull_[i];
            }
        }
        std::cout << "(" << min_x.first << ", " << min_x.second << ") (" << max_x.first << ", " << max_x.second << "): " << distance(min_x, max_x) << "\n";
    }
