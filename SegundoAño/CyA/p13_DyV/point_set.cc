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

#include "point_set.h"

    void point_set::quickHull(void)
    {
        hull_.clear();

        CyA::point min_x_point; 
        CyA::point max_x_point;

        x_bounds(min_x_point, max_x_point);

        quickHull(CyA::line(min_x_point, max_x_point), side::LEFT);
        quickHull(CyA::line(min_x_point, max_x_point), side::RIGHT);

        // Remove duplicates
        std::sort(hull_.begin(), hull_.end());
        hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
    }
     
    void point_set::quickHull(const CyA::line &l, int side)
    {
        CyA::point farthest;

        if (farthest_point(l, side, farthest))
        {
            quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
            quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
        }
        else
        {
            hull_.push_back(l.first);
            hull_.push_back(l.second);
        }
    }

    bool point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const
    {
        farthest = CyA::point_vector::at(0);

        double max_dist = 0;

        bool found = false;

        for (const CyA::point &p : *this)
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

    double point_set::point_2_line(const CyA::line &l, const CyA::point &p) const
    {
        const CyA::point &p1 = l.first;
        const CyA::point &p2 = l.second;

        return (p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first);
    }

    double point_set::distance(const CyA::line &l, const CyA::point &p) const
    {
        return fabs(point_2_line(l, p));
    }

    