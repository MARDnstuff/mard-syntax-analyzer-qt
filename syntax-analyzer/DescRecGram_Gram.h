#ifndef DESCRECGRAM_GRAM_H
#define DESCRECGRAM_GRAM_H
//#include "SimbolosEspeciales.h"
#include <stdlib.h>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include "ClaseNodo.h"
#include "AnalizLexico.h"
#include "ClaseAFD.h"
#include "Estado_AnalizLexico.h"
#include "ElemArreglo.h"




class DescRecGram_Gram{
    public:
        std::string Gramatica;
        AnalizLexico L;
        ElemArreglo ArrReglas[100];
        int NumReglas = 0;
        std::vector<ClaseNodo> Vn; //Conjunto de simbolos no terminales
        std::vector<ClaseNodo> Vt; //Conjunto de simbolos terminales
    public:
        //Constructor vacio;
        DescRecGram_Gram();

        //Constructor
        DescRecGram_Gram(std::string sigma, std::string FileAFD);

        //Establece Gramatica
        bool SetGramatica(std::string sigma);
        ////////PROCESO DE ANALISIS/////////
        bool SecSimbolosP(std::shared_ptr<std::vector<ClaseNodo>> Lista);
        bool SecSimbolos(std::shared_ptr<std::vector<ClaseNodo>> Lista);
        bool LadoDerecho(std::string Simbolo);
        bool LadosDerechosP(std::string Simbolo);
        bool LadosDerechos(std::string Simbolo);
        bool LadoIzquierdo(std::shared_ptr<std::string> Simbolo_ap);
        bool Reglas();
        bool ListaReglasP();
        bool ListaReglas();
        bool G();
        bool AnalizarGramatica();
        ////////////////////////////////////
        //Identifica los simbolos terminales de la gramatica
        void IdentificarTerminales();
        //Funcion FIRST
        std::vector<std::string> First(std::vector<ClaseNodo> l);
        //Función FOLLOW
        std::vector<std::string> Follow(std::string SimbNoTerm);
        //Destructor
        virtual ~DescRecGram_Gram();


};



#endif // DESCRECGRAM_GRAM_H
