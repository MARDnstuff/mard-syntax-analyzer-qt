#ifndef CLASEAFN_H
#define CLASEAFN_H
#include <iostream>
#include "ClaseEstado.h"
#include "SimbolosEspeciales.h"
#include <vector>
#include <stack>

class AFN{

    public: //private:
        int Contador;
        int EdoIni;
        std::vector<Estado> EdoAFN;
        std::vector<Estado> EdoAcept;
        std::vector<char> Alfabeto;
        bool SeAgregoAFNUnionLexico; //sin informacion por el momento
        int IdAFN;
    public:
        //Constructor del AFN
        AFN();

        //Crea un AFN basico para un simbolo
        AFN AFN_Basico (char simb,int Cont);

        //Crea un AFN Basico para un rango de caracteres
        AFN  AFN_Basico (char simb1,char simb2,int Cont);

        //Union de dos AFN
        AFN AFN_Union (AFN automata);

        //Concatenación de  dos AFN
        AFN AFN_Conca (AFN automata);

        //Cerradura positiva de un AFN
        AFN AFN_CerrPOS();

        //Cerradura de Kleene
        AFN AFN_CerrKleene();

        //Operacion opcional (?)
        AFN AFN_Opcional();

        //Regresa el conjunto de estados que son accesible desde "e" con EPSILON
        std::vector<Estado> CerraduraEpsilon(Estado e);

        //Regresa el conjunto de estados que son accesibles desde cada uno
        //de los estados e que estan en el vector con EPSILON
        std::vector<Estado> CerraduraEpsilon(std::vector<Estado> ConjEdos);

        //Regresa el cnjunto de estado a los que me puedo mover con el simbolo
        std::vector<Estado> Mover(std::vector<Estado> Edos,char simb);

        //Regresa el conjunto de estados obtenidos de la cerradura epsilon del conjunto de estados
        //accesibles con un simbolo
        std::vector<Estado> Ir_A(std::vector<Estado> Edos,char simb);

        //Construye la union especial para los AFN
        void AFN_UnionEspecial (AFN f, int Token,int ContadorGlobal);

       //Regresa el contador del ultimo estado creado
       int get_Contador ();
       //Muestra la matriz de adyacencia del AFN
       void Mx_Adyacencia(AFN automata);

        virtual ~AFN();


};

#endif // CLASEAFN_H
