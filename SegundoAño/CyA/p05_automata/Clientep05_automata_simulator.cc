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
#include "estado.h"
#include "automata.h"
#include "alfabeto.h"
#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include "tools.cc"
#include<vector>
#include<algorithm>
#include<iterator>
#include "cadena.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::string linea;
  Alfabeto alfabeto;
  Automata automata;
  int contador = 0;
  std::ifstream archivo_automata;
  archivo_automata.open(argv[1]);
    if (!archivo_automata.is_open()) {
    std::cerr << "Error al abrir el archivo de automata: " << argv[1] << std::endl;
    return 1;  // Salir del programa con un código de error
    }


    //codigo leer archivo
  //leer_archivo(archivo_automata, linea, alfabeto, automata, contador);
    while(getline(archivo_automata, linea)) {
        switch(contador){
            case 0: {
                for (long unsigned int i = 0; i <= linea.length(); i++) {
                    if(linea[i] != ' ' ){
                        alfabeto.Insertar_simbolo(linea[i]);
                    }
                }
								automata.SetAlfabeto(alfabeto);
            break;
            }
            case 1: {
                automata.SetNumeroEstados(stoi(linea));
                break;
            }
            case 2: {
                automata.SetArranque(linea[0]);
            break;
            }
            default: {
                Estado estado = linea[0];
                estado.Set_aceptacion(linea[2]);
                estado.Set_numero_transiciones(linea[4] - '0');
                for(long unsigned int i = 6; i <= linea.length(); i+=4) {
                    if(linea[i] != ' ') {
                        Estado estado2 = linea[i+2];
                        Transicion transicion(estado, linea[i], estado2);
                        automata.Insert(estado, transicion);
                    }
                }
            break;
            }
        }
        contador++;
    }
    archivo_automata.close();
//fin leer archivo



  
  std::ifstream archivo_cadenas;
  archivo_cadenas.open(argv[2]);
  std::string cadena;
  if (!archivo_cadenas.is_open()) {
    std::cerr << "Error al abrir el archivo de cadenas: " << argv[2] << std::endl;
    return 1;  // Salir del programa con un código de error
  }



  //Codigo evaluar cadena
  //Evaluar_cadena(archivo_cadenas, cadena, automata);
     //Bucle que recoge las cadenas del input.txt
    while(getline(archivo_cadenas, cadena)){
        //Conjunto de estados actuales y siguientes
        std::set<Estado> siguientes_estados;
        std::set<Estado> current_estados;
        //Colocamos el estado de arranque como inicial
        //estados_actuales.insert(automata.GetArranque());
      
        for(auto itr = automata.Begin(); itr != automata.End(); ++itr) {
          Estado estado_inicial(itr->first);
          //Si es el estado de inicial
          if(estado_inicial.Get_nombre() == automata.GetArranque()) {
            //siguientes_estados.insert(estado_inicial);
            current_estados.insert(estado_inicial);
          }
        }
        
        //Calculo las epsilon-transiciones de los estados actuales;
        Epsilon_transiciones(current_estados, automata);

        //Procesamos cada simbolo de la cadena
        for(long unsigned int i = 0; i < cadena.length(); ++i) {
            char simbolo_actual(cadena[i]);
            siguientes_estados.clear();

                //Buscamos las transiciones posibles
                
                for (auto j = current_estados.begin(); j != current_estados.end(); ++j) {
                    Estado estado_actual(*j);
                    std::set<Estado> transiciones = automata.ProcesarTransiciones(estado_actual, simbolo_actual);
                    for(auto k = transiciones.begin(); k != transiciones.end(); ++k) {
                        siguientes_estados.insert(*k);
                    }
                }
                
                
                
                //Realizamos el cierre de epsilon en los nuevos estados
                for (auto k = siguientes_estados.begin(); k != siguientes_estados.end(); ++k) {
                    Epsilon_transiciones(siguientes_estados, automata);
                }
                
                //Actualizamos el conjunto de estados actuales
                current_estados = siguientes_estados;
        }/*
        std::cout << cadena;
        if(Comprobar_aceptacion(current_estados)) 
            std::cout <<" --- Accepted\n";
        else
            std::cout << " --- Rejected\n";
        */
    }
    archivo_cadenas.close();
}