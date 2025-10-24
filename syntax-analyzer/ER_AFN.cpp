#include "ER_AFN.h"

//Constructor
ER_AFN::ER_AFN(std::string sigma, AFD AutFD){
    ExprRegular = sigma;
    L = AnalizLexico(ExprRegular,AutFD);
}

//Establece la expresion regular
void ER_AFN::SetExpresion(std::string sigma){
    ExprRegular = sigma;
    L.SetSigma(sigma);
}

//Destructor
ER_AFN::~ER_AFN(){
    //dtor
}

//////////PRCOESO DE EVALUACION///////////

bool ER_AFN:: F(std::shared_ptr<AFN> f_ap){
    int Token;
    char simbolo1, simbolo2;
    Token = L.yylex();
    switch(Token){
        case 60: { //PAR_IZQ
            if(E(f_ap)){
                Token = L.yylex();
                if(Token == 70){ //PAR_DER
                    return true;
                }//if
            }//if
            return false;
            break;
        }
        case 80: { //CORCHETE_IZQ
            Token = L.yylex();
            if(Token == 110){ //SIMBOLO
                simbolo1 = (L.Lexema[0] == '\\')?L.Lexema[1]: L.Lexema[0];
                Token = L.yylex();
                if(Token == 100){ //GUION
                    Token = L.yylex();
                    if(Token == 110){//SIMBOLO
                            simbolo2 = (L.Lexema[0] == '\\')?L.Lexema[1]: L.Lexema[0];
                            Token = L.yylex();
                            if(Token == 90){ //CORCHETE DERECHO
                                *f_ap = f_ap->AFN_Basico(simbolo1,simbolo2,ContarEdo);
                                ContarEdo = f_ap->Contador;
                                return true;
                            }

                    }//if
                }//if
            }//if
            return false;
            break;
        }
        case 110: { //SIMBOLO
            simbolo1 = (L.Lexema[0] == '\\')?L.Lexema[1]: L.Lexema[0];
            *f_ap = f_ap->AFN_Basico(simbolo1,simbolo1,ContarEdo);
            ContarEdo = f_ap->Contador;
            return true;
            break;
        }
    }//switch
    return false;
}

bool ER_AFN :: Cp(std::shared_ptr<AFN> f_ap){
    int Token;
    Token = L.yylex();
    switch(Token){
        case 30: { //CERRADURA POSITIVA
            *f_ap = f_ap->AFN_CerrPOS();
            ContarEdo = f_ap->Contador;
            if(Cp(f_ap)){
                return true;
            }//if
            return false;
            break;
        }
        case 40:{ //CERRADURA DE KLEEN
            *f_ap = f_ap->AFN_CerrKleene();
            ContarEdo = f_ap->Contador;
            if(Cp(f_ap)){
                return true;
            }//if
            return false;
            break;
        }
        case 50:{ // OPCIONAL
            *f_ap = f_ap->AFN_Opcional();
            ContarEdo = f_ap->Contador;
            if(Cp(f_ap)){
                return true;
            }//if
            return false;
            break;
        }
    }//switch
    L.UndoToken();
    return true;
}


bool ER_AFN :: C(std::shared_ptr<AFN> f_ap){
    if(F(f_ap)){
        if(Cp(f_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool ER_AFN :: Tp(std::shared_ptr<AFN> f_ap){
    int Token;
    AFN f2 = AFN();
    std::shared_ptr<AFN> f2_ap(new AFN(f2));
    Token = L.yylex();
    if(Token == 20){//CONCATENACION
        if(C(f2_ap)){
            *f_ap = f_ap->AFN_Conca(*f2_ap);
            ContarEdo = f_ap->Contador;
            if(Tp(f_ap)){
                return true;
            }//if
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;

}

bool ER_AFN :: T(std::shared_ptr<AFN> f_ap){
    if(C(f_ap)){
        if(Tp(f_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool ER_AFN:: Ep(std::shared_ptr<AFN> f_ap){
    int Token;
    AFN f2 = AFN();
    std::shared_ptr<AFN> f2_ap(new AFN(f2));
    Token = L.yylex();
    if(Token == 10){ //OR
        if(T(f2_ap)){
            *f_ap =f_ap->AFN_Union(*f2_ap);
            ContarEdo = f_ap->Contador;
            if(Ep(f_ap)){
                return true;
            }//if
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;
}

bool ER_AFN :: E(std::shared_ptr<AFN> f_ap){
    if(T(f_ap)){
        if(Ep(f_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool ER_AFN::IniConversion(){
    int Token;
    AFN f = AFN();
    std::shared_ptr<AFN> f_ap(new AFN(f));
    if(E(f_ap)){
        Token = L.yylex();
        if(Token == 0){
            result = *f_ap;
            return true;
        }//if
    }//if
    return false;
}
//////////////////////////////////////////
