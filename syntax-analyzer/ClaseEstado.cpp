#include "ClaseEstado.h"
#include <vector>

 //Constructor de un estado
Estado::Estado(){
    EdoAcept1 = false;
    Token1 = -1;
    //aumento -- revisar
    idEstado1 = ContadorIdEstado++;
    Trans1.clear();
    //ctor
}

//Constructor de un estado vacio
Estado Estado :: Estado_null(){
    Estado e = Estado();
    e.set_IdEstado(-1);
    return e;
}

// Regresa id del estado
int Estado:: get_IdEstado(){
    return idEstado1;
}

// Establece el id del estado
void Estado:: set_IdEstado(int id){
    idEstado1 = id;
    return;
}

// Regresa el valor True si es un estado de aceptación
bool Estado:: is_EdoAcept(){
    return EdoAcept1;
}

// Establece el valor a True o False a un estado si es una estado de aceptación
void Estado:: set_EdoAcept(bool value){
    EdoAcept1 = value;
    return;
}

// Regresa el valor del Token unico
int Estado:: get_Token (){
    return Token1;
}

// Establece el valor del Token (valor único)
void Estado:: set_Token(int value){
    Token1 = value;
    return;
}


// Establece el conjunto (o alguna transicion dentro del conjunto) de transiciones
// Agrega a la lista
std::vector<Transicion> Estado :: set_Trans (Transicion value){
    Trans1.push_back(value);
    return Trans1;
}


Estado::~Estado(){
    //dtor
}
