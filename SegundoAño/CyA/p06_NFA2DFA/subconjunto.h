#ifndef SUBCONJUNTO_H_
#define SUBCONJUNTO_H_
#include<set>
#include "node.h"

class Subconjunto {

  public:

    //Constructores
    Subconjunto(void){}
    Subconjunto(int);
    Subconjunto(int, std::set<Node>);
    Subconjunto(Subconjunto& subconjunto); //Constructor de copia

    //Getters
    const int GetName() const;
    const std::set<Node> GetSubconjunto() const;
    const bool GetAceptance() const;

    //Setters
    void SetAceptance();
    void SetName(int);
    void SetSubconjunto(std::set<Node>&);
    void Construir(int, std::set<Node>&);

    //Métodos
    void EpsilosClousure();
    void Insert(Node&);

  private:

    //Atributos de la clase
    int name_;
    std::set<Node> subconjunto_;
    bool aceptance_;

};

#endif //SUBCONJUNTO_H_