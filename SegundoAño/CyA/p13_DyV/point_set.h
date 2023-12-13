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

#pragma once

namespace CyA
{
        typedef std::pair<double,double> point;
        typedef std::pair<point, point> line;
        typedef std::vector<point> point_vector;
 
        enum side
        {
                LEFT = -1,
                CENTER,
                RIGHT
        };
 
        class point_set : public point_vector
        {
        private:
                point_vector hull_;
 
        public:
                point_set(const vector<point> &points);
                ~point_set(void);
 
                void quickHull(void);
 
                void write_hull(std::ostream &os) const;
                void write(std::ostream &os) const;
 
                inline const point_vector& get_hull(void) const { return hull_; }
                inline const point_vector& get_points(void) const { return *this; }
 
        private:
                void quickHull(const line &l, int side);
 
                double distance(const line &l, const point &p) const;
                int find_side(const line &l, const point &p) const;
                void x_bounds(point &min_x, point &max_x) const;
                double point_2_line(const line &l, const point &p) const;
                bool farthest_point(const line &l, int side, point &farthest) const;
        };
}