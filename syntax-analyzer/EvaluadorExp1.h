#ifndef EVALUADOREXP1_H
#define EVALUADOREXP1_H
#include<string>
#include "AnalizLexico.h"
#include "ClaseAFD.h"
#include <memory>

class EvaluadorExp1{
public:
    std::string Expresion;
    float result;
    std::string ExprPost;
    AnalizLexico L;

    public:
        //Constructor con expresion y automata
        EvaluadorExp1(std::string sigma, AFD AutFD);
        //Inicializa la expresion
        void SetExpresion(std::string sigma);
        //destructor
        virtual ~EvaluadorExp1();
        /////////PROCESO DE EVALUACIÓN///////////
        bool F(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap);
        bool Tp(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap);
        bool T(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap);
        bool Ep(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap);
        bool E(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap);
        bool IniEval();
        /////////////////////////////////////////



};

#endif // EVALUADOREXP1_H
