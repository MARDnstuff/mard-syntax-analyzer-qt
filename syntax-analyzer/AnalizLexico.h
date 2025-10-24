#ifndef ANALIZLEXICO_H
#define ANALIZLEXICO_H
#include "Estado_AnalizLexico.h"
#include "ClaseAFD.h"
#include<string>
#include<stack>

class AnalizLexico{
    public:
        std::string Lexema;
    private:
        int token, EdoActual, EdoTransicion;
        std::string CadenaSigma;
        bool PasoPorEdoAcept;
        int IniLexema, FinLexema, IndiceCaracterActual;
        unsigned char CaracterActual;
        std::stack<int> Pila;
        AFD AutomataFD;
    public:
        //Constructor de Analizador lexico
        AnalizLexico();

        //Constructor De Analizador lexico por AFD
        AnalizLexico(std::string sigma, AFD AutFD);

        //Guardar estado actual del analizador lexico
        Estado_AnalizLexico GetEdoAnalizLexico();

        //Establece el estado del analizador lexico
        bool SetEdoAnalizLexico(Estado_AnalizLexico e);

        //Establece la cadena Sigma(cadena que se va analizará)
        void SetSigma(std::string sigma);

        //Regresa el token del analisis (hace el analisis)
        int yylex();

        //Funcion UndoToken
        bool UndoToken();

        //Destructor
        virtual ~AnalizLexico();



};

#endif // ANALIZLEXICO_H
