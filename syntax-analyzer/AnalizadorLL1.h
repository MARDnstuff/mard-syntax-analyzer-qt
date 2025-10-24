#ifndef ANALIZADORLL1_H
#define ANALIZADORLL1_H
#include <vector>
#include <string>
#include "DescRecGram_Gram.h"
#include "AnalizLexico.h"
#include "SimbTerm.h"
#include "ClaseNodo.h"
#include "Simb.h"
#include <stack>

class AnalizadorLL1{
    public:
        std::string flag;
        int flag2 = -1;
        DescRecGram_Gram DescRecG;
        AnalizLexico LexGram;
        std::string Gram;
        std::string Sigma;
        int **TablaLL1;
        int row;
        int column;
        SimbTerm *Vt;
        std::string *Vt2;
        int *Vt3; //recordar inicializar
        std::string *Vn;
        std::string AFDFile_ = "AFD_GramGram.txt";
    public:
        AnalizadorLL1();
        //Constructor por gramatica y nombre del archivo del AFD
        AnalizadorLL1(std::string CadGramatica, std::string ArchAFDLexic);
         //Constructor por gramatica
        AnalizadorLL1(std::string CadGramatica);
        //Establece el archivo del que se saca el Analizador lexico
        void SetLexico(std::string ArchAFDLexic );
        //Crea Tabla LL1
        void CrearTablaLL1();
        //Analisador sintactico LL1
        bool AnalizSintacLL1(std::string Sigma);
        //Destructor vritual
        virtual ~AnalizadorLL1();


};

#endif // ANALIZADORLL1_H
