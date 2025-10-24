#include "AnalizLexico.h"

//Constructor de Analizador lexico
AnalizLexico::AnalizLexico(){
    CadenaSigma="";
    PasoPorEdoAcept = false;
    IniLexema = -1;
    FinLexema = -1;
    IndiceCaracterActual = -1;
    token = -1;
    AutomataFD = AFD();
    //ctor
}

//Constructor De Analizador lexico por AFD
AnalizLexico:: AnalizLexico(std::string sigma, AFD AutFD){
    CadenaSigma =  sigma;
    PasoPorEdoAcept = false;
    IniLexema = 0;
    FinLexema = -1;
    IndiceCaracterActual = 0;
    token =-1;
    AutomataFD = AutFD;
}

//Guardar estado actual del automata
Estado_AnalizLexico  AnalizLexico :: GetEdoAnalizLexico(){
    Estado_AnalizLexico EdoActualAnaliz = Estado_AnalizLexico();
    EdoActualAnaliz.CaracterActual = CaracterActual;
    EdoActualAnaliz.EdoTransicion = EdoTransicion;
    EdoActualAnaliz.FinLexema = FinLexema;
    EdoActualAnaliz.IndiceCaracterActual = IndiceCaracterActual;
    EdoActualAnaliz.IniLexema = IniLexema;
    EdoActualAnaliz.Lexema = Lexema;
    EdoActualAnaliz.PasoPorEdoAcept = PasoPorEdoAcept;
    EdoActualAnaliz.token = token;
    return EdoActualAnaliz;
}

//Establece el estado del analizador lexico
bool AnalizLexico :: SetEdoAnalizLexico(Estado_AnalizLexico e){
    CaracterActual = e.CaracterActual;
    EdoActual = e.EdoActual;
    EdoTransicion = e.EdoTransicion;
    FinLexema = e.FinLexema;
    IndiceCaracterActual = e.IndiceCaracterActual;
    IniLexema = e.IniLexema;
    Lexema = e.Lexema;
    PasoPorEdoAcept = e.PasoPorEdoAcept;
    token = e.token;
    Pila = e.Pila;
    return true;
}

//Establece la cadena Sigma(cadena que se va analizará)
void AnalizLexico::SetSigma(std::string sigma){
    CadenaSigma = sigma;
    PasoPorEdoAcept = false;
    IniLexema = 0;
    FinLexema = -1;
    IndiceCaracterActual = 0;
    token = -1;
}

//Regresa el token del analisis (hace el analisis)
int AnalizLexico::yylex(){
    while(true){
            Pila.push(IndiceCaracterActual);
            int tam = (int) CadenaSigma.length(); //revisar condicion
            if(IndiceCaracterActual >= tam){
                Lexema = "";
                return FIN;
            }//if

            IniLexema = IndiceCaracterActual;
            EdoActual = 0;
            PasoPorEdoAcept = false;
            FinLexema = -1;
            token = -1;
            while(IndiceCaracterActual < tam){//revisar ccondicion
                CaracterActual = CadenaSigma.at(IndiceCaracterActual);
                EdoTransicion = AutomataFD.Mx_adyacencia[EdoActual][CaracterActual]; //reviar indices (cast a int)
                if(EdoTransicion != -1){
                    //Existe transicion
                    if(AutomataFD.Mx_adyacencia[EdoTransicion][256] != -1){
                        //Esta en estado de aceptacion
                        PasoPorEdoAcept = true;
                        token = AutomataFD.Mx_adyacencia[EdoTransicion][256];
                        FinLexema = IndiceCaracterActual;
                    }//if
                    IndiceCaracterActual++;
                    EdoActual = EdoTransicion;
                    continue;
                }//if
                break;
                //No hay transicion del estado actual con el caracter actual
            }//while

            if(!PasoPorEdoAcept){
                IndiceCaracterActual = IniLexema + 1;
                Lexema = CadenaSigma.substr(IniLexema,1);
                token = ERROR;
                return token; //ERROR
            }//if
            //No hay transicion con el caracter actual, pero ya se habia pasado por el edo de Aceptacion
            Lexema = CadenaSigma.substr(IniLexema, FinLexema - IniLexema + 1);
            IndiceCaracterActual = FinLexema + 1;
            if(token == OMITIR){
                continue;
            }else{
                return token;
            }//if

    }//while

}

//Funcion UndoToken
bool AnalizLexico :: UndoToken(){
    int tam_Pila = (int) Pila.size();
    if(tam_Pila == 0){
        return false;
    }//if
    IndiceCaracterActual = Pila.top();
    Pila.pop();
    return true;
}

AnalizLexico::~AnalizLexico(){

    //dtor
}
