#include "Simb.h"

Simb::Simb()
{
    //ctor
}

Simb::Simb(std::string Cadena,bool esTerminal, int token){
    cadena = Cadena;
    Terminal = esTerminal;
    Token = token;
}

Simb::~Simb()
{
    //dtor
}
