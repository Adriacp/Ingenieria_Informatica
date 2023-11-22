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
#ifndef AUTOMATA_H_
#define AUTOMATA_H_
#include<map>
#include<string>
#include "estado.h"
#include "transicion.h"
#include "alfabeto.h"
#include "cadena.h"

class Automata {

  public:

    //Constructores
    Automata(int numero_estados, int arranque) {numero_estados_ = numero_estados; arranque_ = arranque;}
    Automata(){}

    //Getter
    char GetArranque(){return arranque_;}
    int GetNumEstados(){return numero_estados_;}
    Alfabeto GetAlfabeto() {return alfabeto_;}
    std::multimap<Estado, Transicion> GetMultimap(){return multimap_;}
    std::set<Estado> GetEstadoDestino(std::set<Estado>&, char);
    std::multimap<Estado, Transicion>::iterator GetLowerBound(Estado &estado) {return multimap_.lower_bound(estado);}
    std::multimap<Estado, Transicion>::iterator GetUpperBound(Estado &estado) {return multimap_.upper_bound(estado);}

    //Setter
    void SetNumeroEstados(int numero) {numero_estados_ = numero;}
    void SetAlfabeto(Alfabeto& a) {alfabeto_ = a;}
    void SetArranque(int arranque) {arranque_ = arranque;}

    //Métodos
    bool Search_multimap(std::set<Estado>&, char);
    void Insert(Estado& estado, Transicion& transicion){multimap_.emplace(estado, transicion);}
    std::multimap<Estado, Transicion>::iterator Begin(){return multimap_.begin();}
    std::multimap<Estado, Transicion>::iterator End(){return multimap_.end();}
    bool EstaEnLenguaje(char si);
    std::set<Estado> ProcesarTransiciones(Estado&, char);
    
    //Sobrecargas
    friend std::ostream &operator<<(std::ostream &os, Automata p);
  
  private:

    std::multimap<Estado, Transicion> multimap_;
    int numero_estados_;
    char arranque_;
    Alfabeto alfabeto_;

};

#endif //AUTOMATA_H_