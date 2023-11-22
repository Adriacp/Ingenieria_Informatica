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
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include "estado.h"
#include "automata.h"

void Usage(int argc, char* argv[]) {
std::string kHelpertext = "Modo de empleo: ./p05_automata_simulator input.fa input.txt\nPruebe 'p05_automata_simulator --help' para más información.";
    if(argc < 2) {
        std::cout <<kHelpertext << std::endl;
        exit(EXIT_SUCCESS);
    }
    std::string parameter = argv[1];
    if(parameter == "--help") {
      std::cout << "El programa recibe un fichero que especifica el autómata y otro fichero de texto\nen el que figuran una serie de cadenas sobre el alfabeto del autómata especificado" << std::endl;
      exit(EXIT_SUCCESS);
    }
    else if(argc < 3 || argc > 3) {
        std::cout << kHelpertext << std::endl;
        exit(EXIT_SUCCESS);
    }
}
/*
void Imprimir_vector(std::vector<char> v) {
    for(long unsigned int i = 0; i < v.size(); i++) { 
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
*/
/*
void Epsilon_transisiones(std::set<Estado> estado_siguiente, Automata& automata) {
  for(auto itr = automata.Begin(); itr != automata.End(); itr++) {
      for(std::set<Estado>::iterator i = estado_siguiente.begin(); i != estado_siguiente.end(); i++) {
        if(itr->first == *i && itr->second.Get_simbolo() == '&') {
          for(std::set<Estado>::iterator j = itr->second.Get_estado().begin(); j != itr->second.Get_estado().end(); j++)
            estado_siguiente.insert(*j);
        }
      }
  }
}
*/

void imprimir_set(std::set<Estado> a) {
    for(auto itr = a.begin(); itr !=a.end(); ++itr) {
        std::cout << *itr;
    }
}


bool Comprobar_aceptacion(std::set<Estado> estados) {
	bool resultado = false;
	for(std::set<Estado>::iterator itr = estados.begin(); itr != estados.end(); itr++) {
		if(itr->Get_Aceptacion())
			resultado = true;
	}
	return resultado;
}
void Epsilon_transiciones(std::set<Estado> estado_siguiente, Automata& automata) {
    for(auto itr = automata.Begin(); itr != automata.End(); ++itr) {
        for(auto i = estado_siguiente.begin(); i != estado_siguiente.end(); ++i) {
            if(itr->first == *i && itr->second.GetSimboloTransicion() == '&') {
                for(auto j = automata.GetMultimap().lower_bound(itr->first); j != automata.GetMultimap().upper_bound(itr->first); ++j) {
                    estado_siguiente.insert(j->second.GetTransicion());
                }
            }
        }
    }
}
/*
std::set<Estado> Procesar_transiciones(Estado &estado, char simbolo_actual, Automata &automata) {
    //nodos a los que transita, uso un set ya que puede haber mas de un estado.
    std::set<Estado> siguiente_estado;

    //Recorremos las transiciones del estado especificado
    
    for (auto i = automata.GetMultimap().lower_bound(estado); i != automata.GetMultimap().upper_bound(estado); ++i) {
        Transicion transicion_actual(i -> second);
        //Si el simbolo de la cadena coincide con el simbolo de la transicion
        char simbolo_aux = simbolo_actual;
        //Cadena cadena_auxiliar(simbolo_aux);
        if ( transicion_actual.GetSimboloTransicion() == simbolo_actual && automata.EstaEnLenguaje(simbolo_aux)) {
            //Recorremos el automata para copiar el estado de transicion
            for(auto j = automata.Begin(); j != automata.End(); ++j) {
                //creamos el estado siguiente
                Estado estado_aux(j->first);
                //Si el estado al que transita == estado en el automata
                if(estado_aux == transicion_actual.GetTransicion()) {
                    Estado nuevo_estado(transicion_actual.GetTransicion().Get_nombre(), estado_aux.Get_Aceptacion());
                    siguiente_estado.insert(nuevo_estado);
                }
            }
        }
    }
    
    return siguiente_estado;
}
*/
/*
void Evaluar_cadena(std::ifstream &archivo_cadenas, std::string cadena, Automata &automata) {
    //Bucle que recoge las cadenas del input.txt
    while(getline(archivo_cadenas, cadena)){
        //Conjunto de estados actuales y siguientes
        std::set<Estado> siguientes_estados;
        std::set<Estado> estados_actuales;
        //Colocamos el estado de arranque como inicial
        estados_actuales.insert(automata.GetArranque());

        //Calculo las epsilon-transiciones de los estados actuales;
        Epsilon_transiciones(estados_actuales, automata);

        //Procesamos cada simbolo de la cadena
        for(long unsigned int i = 0; i < cadena.length(); ++i) {
            char simbolo_actual(cadena[i]);
            siguientes_estados.clear();

                //Buscamos las transiciones posibles
                
                for (auto j = estados_actuales.begin(); j != estados_actuales.end(); ++j) {
                    Estado estado_actual(*j);
                    std::set<Estado> transiciones = Procesar_transiciones(estado_actual, simbolo_actual, automata);
                    for(auto k = transiciones.begin(); k != transiciones.end(); ++k) {
                        siguientes_estados.insert(*k);
                    }
                }
                
                
                //Realizamos el cierre de epsilon en los nuevos estados
                for (auto k = siguientes_estados.begin(); k != siguientes_estados.end(); ++k) {
                    Epsilon_transiciones(siguientes_estados, automata);
                }
                
                //Actualizamos el conjunto de estados actuales
                estados_actuales = siguientes_estados;
        }
        std::cout << cadena;
        if(Comprobar_aceptacion(estados_actuales)) 
            std::cout <<" --- Accepted\n";
        else
            std::cout << " --- Rejected\n";
    }
    archivo_cadenas.close();
}
*/
std::ostream &operator<<(std::ostream &os, std::set<Estado> estados) {
    for(auto itr = estados.begin(); itr != estados.end(); ++itr) {
        (itr == estados.end()--) ? std::cout << *itr : std::cout << *itr << " ";
    }
    return os;
}

void Insert(std::set<Estado> s, Estado& e) {
    s.insert(e);
}

void leer_archivo(std::ifstream &archivo_automata, std::string linea, Alfabeto &alfabeto, Automata &automata, int contador) {
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
                estado.Set_aceptacion(linea[2] - '0');
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
}

/*
std::vector<char> Guardar_estados(std::set<Estado> estado) {
    std::vector<char> resultado;
    for(std::set<Estado>::iterator itr = estado.begin(); itr != estado.end(); itr++) {
        resultado.push_back(itr->Get_nombre());
    }
    return resultado;
}
*/

/*
void trabajar_con_input(std::ifstream &archivo_cadenas, std::string cadena, Automata& automata) {
    std::set<Estado> estado_actual;
    estado_actual.insert(automata.Get_arranque());
    std::set<Estado> estado_siguiente;
    Epsilon_transisiones(estado_actual, automata);
    while(getline(archivo_cadenas, cadena)) {
      for(long unsigned int i = 0; i < cadena.length(); i++) {
       if(automata.Get_alfabeto().Comprobar_simbolo(cadena[i])) {
        //if(automata.Search_multimap(estado_actual, cadena[i])) {
          estado_siguiente = automata.Get_estado_destino(estado_actual, cadena[i]);
        //}
        Epsilon_transisiones(estado_siguiente, automata);
        estado_actual = estado_siguiente;
       }
      }
        std::cout << cadena;
        if(Comprobar_aceptacion(estado_actual)) 
         std::cout <<" --- Accepted\n";
        else
         std::cout << " --- Rejected\n";
    }
}
*/


//Parámetros: archivo con las cadenas, cadena, automata.