#ifndef CONIJ_H
#define CONIJ_H
#include "ClaseEstado.h"
#include "ClaseTransicion.h"
#include<vector>

class ConIj {
    public:
        std::vector<Transicion> Trans1;
        bool Acept;
        int Token;
    private:
        int Id;
        std::vector<Estado> Edos;

    public:
        //Constructor
        ConIj();
        //Regresa el Id del Conjunto Ij
        int get_ConIj_ID ();
        //Establece el ID del Conjunto Ij
        void set_ConIj_ID (int ID);
        //Regresa el conjunto de estados asociados al Conjunto Ij
        std::vector<Estado> get_ConIj_Edos ();
        //Añade un Estado al conjunto de estados asoicados al Conjunto Ij
        void set_Element_ConIJ(Estado e);
        //Establece por completo el conjunto de estados asosicados al Conjunot Ij
        void set_ConIJ_Edos(std::vector<Estado> e);
        //Regresa true si el Conjunto se encuentra ya en el arreglo
        int equals_to (std::vector<ConIj> e1,std::vector<Estado> e2);


};



#endif // CONIJ_H
