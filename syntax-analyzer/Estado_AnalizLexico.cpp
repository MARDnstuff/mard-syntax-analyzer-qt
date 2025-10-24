#include "Estado_AnalizLexico.h"

Estado_AnalizLexico::Estado_AnalizLexico(){
    token = 0;
    EdoActual = 0;
    EdoTransicion = -1;
    Lexema = "";
    PasoPorEdoAcept = false;
    IniLexema = -1;
    FinLexema = -1;
    IndiceCaracterActual = -1;
    CaracterActual= ' ';
}

Estado_AnalizLexico::~Estado_AnalizLexico(){
    //dtor
}
