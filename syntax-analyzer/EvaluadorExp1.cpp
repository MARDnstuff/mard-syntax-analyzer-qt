#include "EvaluadorExp1.h"

//Constructor con expresion y automata
EvaluadorExp1::EvaluadorExp1(std::string sigma, AFD AutFD){
    Expresion = sigma;
    L = AnalizLexico(Expresion,AutFD);
    //ctor
}

//Inicializa la expresion
void EvaluadorExp1:: SetExpresion(std::string sigma){
    Expresion = sigma;
    L.SetSigma(sigma);

}


///////PROCESO DE EVALUACIÓN/////////
bool EvaluadorExp1 :: F(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap){
    int Token;
    Token = L.yylex();
    switch(Token){
        case 60:{//Parentesis izquierdo
            if(E(v_ap,Postfijo_ap)){
                Token = L.yylex();
                if(Token == 70){//Parentesis derecho
                    return true;
                }//if
            }//if
            return false;
            break;
        }//case
        case 10:{ //NUM
            *v_ap = std::stof(L.Lexema);
            *Postfijo_ap = L.Lexema;
            return true;
        }//case
    }//switch
    return false;
}

bool EvaluadorExp1 :: Tp(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap){
    int Token;
    float v2 = 0;
    std::string Postfijo2 = "";
    std::shared_ptr<float> v2_ap(new float(v2));
    std::shared_ptr<std::string> Postfijo2_ap(new std::string(Postfijo2));
    Token = L.yylex();

    if(Token == 40 || Token == 50){//* o /
        if(F(v2_ap,Postfijo2_ap)){
            *v_ap = (*v_ap) * (Token == 40 ? (*v2_ap) : 1/(*v2_ap));
            *Postfijo_ap = (*Postfijo_ap) + " " + (*Postfijo2_ap) + " " +(Token == 40 ? "*" : "/");
            if(Tp(v_ap,Postfijo_ap)){
                return true;
            }//if
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;

}

bool EvaluadorExp1 :: T(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap){
    if(F(v_ap,Postfijo_ap)){
        if(Tp(v_ap,Postfijo_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool EvaluadorExp1 :: Ep(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap){
    int Token;
    float v2 = 0;
    std::string Postfijo2 = "";
    std::shared_ptr<float> v2_ap(new float(v2));
    std::shared_ptr<std::string> Postfijo2_ap(new std::string(Postfijo2));
    Token = L.yylex();

    if(Token == 20 || Token == 30){//+ o -
        if(T(v2_ap,Postfijo2_ap)){
            *v_ap = *v_ap + (Token == 20 ? (*v2_ap) : -(*v2_ap));
            *Postfijo_ap = (*Postfijo_ap) + " " + (*Postfijo2_ap) + " " +(Token == 20 ? "+" : "-");
            if(Ep(v_ap,Postfijo_ap)){
                return true;
            }//if
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;

}

bool EvaluadorExp1::E(std::shared_ptr<float> v_ap, std::shared_ptr<std::string> Postfijo_ap){
    if(T(v_ap,Postfijo_ap)){
        if(Ep(v_ap,Postfijo_ap)){
            return true;
        }//if
    }//if
    return false;
}


bool EvaluadorExp1 :: IniEval(){
    int Token;
    float v = 0;
    std::string Postfijo="";
    std::shared_ptr<float> v_ap(new float(v));
    std::shared_ptr<std::string> Postfijo_ap(new std::string(Postfijo));

    if(E(v_ap,Postfijo_ap)){
        Token = L.yylex();
        if(Token == 0){
            v = *v_ap;
            Postfijo = *Postfijo_ap;
            result = v;
            ExprPost = Postfijo;
            return true;
        }//if
    }//if
    return false;
}


/////////////////////////////////////

EvaluadorExp1::~EvaluadorExp1(){
    //dtor
}
