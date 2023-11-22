// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9:  Simulación de maquinas de Turing
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 13/11/2023
// Archivo turingmachine.h: Archivo con la definicion de la clase turingmachine.h
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 27/10/2023 - Creación del código

//Aseguro que el codigo fuente que lo invoca sea incluido una sola vez
#pragma once
#include <set>
#include "node.h"
#include "alphabet.h"
#include <fstream>
#include <vector>
#include <map>

class TuringMachine {

  public:
    //Constructor turingmachine
    TuringMachine(std::ifstream& input_TM);

    //Método
    void IsAMovement(Symbol& symbol); //comprueba si es un movimiento valido en la maquina de turing
    void IsANode(Node &node);
    void Imprimirmap();
    void Simulate(std::ifstream &input_tape); //simulacion con el archivo que contiene la cadena.
    void CalculateMove(Node &actual);
    bool Comprobacion(Node& actual);
    bool IsAccepted(Node &node);
    
  private:
    
    long unsigned int header_; // posicion de la cabecera
    int num_nodes;
    std::set<Node> nodes_;
    std::set<Node> end_nodes_;
    //Alphabet alphabet_;
    Alphabet tape_alphabet_;
    Node initial_;
    std::vector<Symbol> tape_;
    int tuplenum_;
    std::multimap<Node, std::pair<std::pair<Symbol, Symbol>, std::pair<Symbol, Node>>> tuples_;

    //conjunto de estados
    //cinta
    //cabecera puntero a la cinta

};