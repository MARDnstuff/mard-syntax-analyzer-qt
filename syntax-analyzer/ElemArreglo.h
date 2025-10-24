#ifndef ELEMARREGLO_H
#define ELEMARREGLO_H
#include <vector>
#include "ClaseNodo.h"

class ElemArreglo{
    public:
        ClaseNodo InfSimbolo;
        std::vector<ClaseNodo> ListaLadoDerecho;
    public:
        ElemArreglo();
        virtual ~ElemArreglo();
};

#endif // ELEMARREGLO_H
