#ifndef CHAIN_H_
#define CHAIN_H_
#include<string>

class Cadena {

  public:

    //Constructores
    Cadena() {}
    Cadena(std::string cadena) {cadena_ = cadena;}
    Cadena(char simbolo) {cadena_.push_back(simbolo);}
    Cadena(Cadena& cadena) {cadena_ = cadena.GetCadena();}

    //Getters
    std::string GetCadena() {return cadena_;}

    //Métodos
    int length() {return cadena_.length();}
    char at(int i) {return cadena_[i];}

    //Sobrecarga
    char operator[](char i) {return cadena_.at(i);}

  private:

    std::string cadena_;

};

#endif //CHAIN_H_