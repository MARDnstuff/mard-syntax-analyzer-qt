#ifndef ESTADO_ANALIZLEXICO_H
#define ESTADO_ANALIZLEXICO_H
#include <string>
#include <stack>

class Estado_AnalizLexico{
    public:
        int token;
        int EdoActual;
        int EdoTransicion;
        std::string Lexema;
        bool PasoPorEdoAcept;
        int IniLexema;
        int FinLexema;
        int IndiceCaracterActual;
        char CaracterActual;
        std::stack<int> Pila;

    public:
        Estado_AnalizLexico();
        virtual ~Estado_AnalizLexico();



};

#endif // ESTADO_ANALIZLEXICO_H
