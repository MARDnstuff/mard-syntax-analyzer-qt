#include "SimbTerm.h"

SimbTerm :: SimbTerm(std::string Simb, int Token){
    Simbolo = Simb;
    ValToken = Token;
}

SimbTerm::SimbTerm(){
    Simbolo = "";
    ValToken = -1;
    //ctor
}

SimbTerm::~SimbTerm()
{
    //dtor
}
