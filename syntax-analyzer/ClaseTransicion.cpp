#include "ClaseTransicion.h"

// Constructor para un solo simbolo
Transicion::Transicion(char simb, int idEdo_o, int idEdo_d){
    SimbInf1 = simb;
    SimbSup1 = simb;
    idEdo_origen = idEdo_o;
    idEdo_destino = idEdo_d;
    //ctor
}
// Constructor para un rango de simbolos
Transicion ::Transicion (char simb1, char simb2, int idEdo_o ,int idEdo_d){
    SimbInf1 = simb1;
    SimbSup1 = simb2;
    idEdo_origen = idEdo_o;
    idEdo_destino = idEdo_d;
}
// Constructor sin transición
Transicion :: Transicion(){ // posible dilema
    SimbInf1 = 00;
    SimbSup1 = 00;
    idEdo_origen = -1;
    idEdo_destino = -1;
}
// Establece Transición para un solo simbolo
void Transicion :: set_Transicion(char s1,int idEdo_o ,int idEdo_d){
    SimbInf1 = s1;
    SimbSup1 = s1;
    idEdo_origen = idEdo_o;
    idEdo_destino = idEdo_d;
    return;
}
// Establece Transición por rango
void Transicion :: set_Transicion_r(char s1,char s2, int idEdo_o ,int idEdo_d){
    SimbInf1 = s1;
    SimbSup1 = s2;
    idEdo_origen = idEdo_o;
    idEdo_destino = idEdo_d;
    return;
}

// Regresa el Simbolo inferior
char Transicion :: get_SimbInf (){
    return SimbInf1;
}
// Establece el Simbolo inferior
void Transicion :: set_SimbInf (char value){
    SimbInf1 = value;
    return;
}
// Regresa el Simbolo superior
char Transicion :: get_SimbSup (){
    return SimbSup1;
}
// Establece el Simbolo superior
void Transicion :: set_SimbSup(char value){
    SimbSup1 = value;
    return;
}
// Regresa el estado al que tiene transición con el caracter S
int Transicion :: get_EdoTrans (char simb){
    if(SimbInf1 <= simb && simb <= SimbSup1){
        return idEdo_destino;
    }
    return -1;
}

// Establece el estado origen
void Transicion :: set_EdoOrigen (int idEdo_o){
    idEdo_origen = idEdo_o;
    return;
}

// Regresa el estado origen
int Transicion :: get_EdoOrigen (){
    return idEdo_origen;
}

// Establece el estado destino
void Transicion :: set_EdoDestino (int idEdo_d){
    idEdo_destino = idEdo_d;
    return;
}

// Regresa el estado destino
int Transicion :: get_EdoDestino (){
    return idEdo_destino;
}

Transicion::~Transicion(){
    //dtor
}
