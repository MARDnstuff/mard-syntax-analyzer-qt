#include "ClaseNodo.h"

ClaseNodo :: ClaseNodo(){
    Simbolo = "";
    Terminal =  false;
}

ClaseNodo :: ClaseNodo(std::string Simb){
    Simbolo = Simb;
    Terminal = false;

}

ClaseNodo :: ClaseNodo(std::string Simb, bool EsTerminal){
    Simbolo = Simb;
    Terminal = EsTerminal;
}


ClaseNodo::~ClaseNodo(){
    //dtor
}
