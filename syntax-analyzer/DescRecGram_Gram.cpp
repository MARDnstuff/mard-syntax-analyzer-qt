#include "DescRecGram_Gram.h"
//funciones auxiliares
bool contain (std::vector<std::string> n1 , std::string cadena){
    for(std::string s: n1){
        if(cadena == s){
            return true;
        }//if
    }//for
    return false;
}

bool contain2 (std::vector<ClaseNodo> n1 , std::string cadena){
    for(ClaseNodo N: n1){
        if(cadena == N.Simbolo){
            return true;
        }//if
    }//for
    return false;
}

int WhereIS_contain (std::vector<std::string> n1 , std::string cadena){
    int tam = (int) n1.size();

    for(int i=0; i<tam; i++){
        if(cadena == n1.at(i)){
            return i;
        }//if
    }//for
    return -1;
}

//Constructor vacio;
DescRecGram_Gram  :: DescRecGram_Gram(){}

//Constructor
DescRecGram_Gram :: DescRecGram_Gram(std::string sigma, std::string FileAFD){
    Gramatica = sigma;
    AFD p = AFD();
    p.Carga_TablaAFD(FileAFD);
    AnalizLexico p2 = AnalizLexico(Gramatica,p);
    L = p2;
    Vn.clear();
    Vt.clear();
}

//Establece Gramatica
bool DescRecGram_Gram:: SetGramatica(std::string sigma){
    Gramatica = sigma;
    L.SetSigma(sigma);
    return true;
}

////////PROCESO DE ANALISIS/////////
bool DescRecGram_Gram :: SecSimbolosP(std::shared_ptr<std::vector<ClaseNodo>> Lista){
    int token;
    ClaseNodo N;
    token = L.yylex();
    if(token == SIMBOLO){
        N = ClaseNodo(L.Lexema,false);
        if(SecSimbolosP(Lista)){
            Lista->insert(Lista->begin(),N);
            //Lista->push_back(N);
            return true;
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;
}

bool DescRecGram_Gram :: SecSimbolos(std::shared_ptr<std::vector<ClaseNodo>> Lista){
    int token;
    ClaseNodo N;
    token = L.yylex();
    if(token == SIMBOLO){
        N = ClaseNodo(L.Lexema);
        if(SecSimbolosP(Lista)){
            Lista->insert(Lista->begin(),N);
            //Lista->push_back(N);
            return true;
        }//if
    }//if
    return false;
}
//std::shared_ptr<std::string> Simbolo_ap
//std::string Simbolo

bool DescRecGram_Gram:: LadoDerecho(std::string Simbolo){//Simbolo es el lado izquierdo de la regla gramatical
    std::vector<ClaseNodo> Lista;
    Lista.clear();
    std::shared_ptr<std::vector<ClaseNodo>> Lista_ap(new std::vector<ClaseNodo>(Lista));
    if(SecSimbolos(Lista_ap)){
        ArrReglas[NumReglas] = ElemArreglo();
        ArrReglas[NumReglas].InfSimbolo = ClaseNodo(Simbolo);
        ArrReglas[NumReglas++].ListaLadoDerecho = *Lista_ap; //revisar
        return true;
    }//if
    return false;
}
//std::shared_ptr<std::string> Simbolo_ap
//std::string Simbolo
bool DescRecGram_Gram :: LadosDerechosP(std::string Simbolo){
    int token;
    token = L.yylex();
    if(token == OR){
        if(LadoDerecho(Simbolo)){
            if(LadosDerechosP(Simbolo)){
                return true;
            }//if
        }//if
    }//if
    L.UndoToken();
    return true;
}

//std::shared_ptr<std::string> Simbolo_ap
//std::string Simbolo
bool DescRecGram_Gram :: LadosDerechos(std::string Simbolo){
    if(LadoDerecho(Simbolo)){
        if(LadosDerechosP(Simbolo)){
            return true;
        }//if
    }//if
    return false;
}

bool DescRecGram_Gram :: LadoIzquierdo(std::shared_ptr<std::string> Simbolo_ap){
        int token;
        token = L.yylex();
        if(token == SIMBOLO){
            *Simbolo_ap = L.Lexema;
            return true;
        }//if
        return false;
}

bool DescRecGram_Gram ::Reglas(){
    int token;
    std::string Simbolo = "";
    std::shared_ptr<std::string> Simbolo_ap(new std::string(Simbolo));
    if(LadoIzquierdo(Simbolo_ap)){
        Simbolo = *Simbolo_ap;
        ClaseNodo n = ClaseNodo(*Simbolo_ap);
        Vn.push_back(n);
        token = L.yylex();
        if(token == FLECHA){
            if(LadosDerechos(Simbolo)){
                return true;
            }//if
        }//if
    }//if
    return false;
}


bool DescRecGram_Gram :: ListaReglasP(){
    int token;
    Estado_AnalizLexico e;
    e = L.GetEdoAnalizLexico();
    if(Reglas()){
       token = L.yylex();
       if(token == PC){
            return true;
       }//if
       return false;
    }//if
    //caso epsilon
    return true;
}

bool DescRecGram_Gram :: ListaReglas(){
    int token;
    if(Reglas()){
        token = L.yylex();
        if(token == PC ){
            return true;
        }//if
    }//if
    return false;
}

bool DescRecGram_Gram :: G(){
    if(ListaReglas()){
        return true;
    }//if
    return false;
}

bool DescRecGram_Gram :: AnalizarGramatica(){
    int token;
    if(G()){
        token = L.yylex();
        if(token == 0){
            return true;
        }else{
            L.UndoToken();
            return AnalizarGramatica();
        }
    }//if
    return false;
}
////////////////////////////////////


//Identifica los simbolos terminales de la gramatica
void DescRecGram_Gram :: IdentificarTerminales(){
    int j=0; //checar si se considera epsilon como terminal
    for(int i=0; i<NumReglas; i++){
            j=0;
        for(ClaseNodo N: ArrReglas[i].ListaLadoDerecho){
            if(!contain2(Vn,N.Simbolo)){
                if(Vt.empty() || !contain2(Vt,N.Simbolo)){
                        if(N.Simbolo != "epsilon"){
                            ArrReglas[i].ListaLadoDerecho.at(j).Terminal = true;
                            N.Terminal = true;
                            Vt.push_back(N);
                        }//if
                }//if
                if(N.Simbolo == "epsilon"){
                    ArrReglas[i].ListaLadoDerecho.at(j).Terminal = true;
                }//ir
            }//if
            j++;
        }//for
    }//for


    return;
}

//Funcion FIRST
std::vector<std::string> DescRecGram_Gram :: First(std::vector<ClaseNodo> l){
    ClaseNodo N;
    std::vector<std::string> R;
    R.clear();
    if(l.empty()){
        return R;
    }//if
    int tam_vec = (int) l.size();
    for(int j=0; j< tam_vec; j++){
        N = l.at(j);
        if(N.Terminal || N.Simbolo == "epsilon"){
            R.push_back(N.Simbolo);
            return R;
        }//if
        //N es no terminal, se calcula el first de cada lado derecho de este no terminal
        for(int i =0; i<NumReglas; i++){
            if(ArrReglas[i].ListaLadoDerecho.at(0).Simbolo == N.Simbolo){
               continue;
            }//if
            if(ArrReglas[i].InfSimbolo.Simbolo == N.Simbolo){

                for(std::string s: First(ArrReglas[i].ListaLadoDerecho)){
                    R.push_back(s);
                }//for
            }//if

        }//for
       if(contain(R,"epsilon")){
                //posible problema
            int tam_l = (int) l.size();
            if(j == (tam_l - 1)){
                    continue;
            }else{

                R.erase(R.begin()+WhereIS_contain(R,"epsilon"));
            }//if
        }else{
            break;
        }//if
    }//for
    return R;
}

/*Terminar de poner todo de Follow y creación de Tabla LL(1) y el algoritmo de anlisis sintactico */
    /* Hacer pruebas y la implementación en Qt*/

//Función FOLLOW
std::vector<std::string> DescRecGram_Gram :: Follow(std::string SimbNoTerm){
    std::vector<std::string> R;
    std::vector<std::string> Aux;
    std::vector<ClaseNodo> ListaPost;
    R.clear();
    if(ArrReglas[0].InfSimbolo.Simbolo == SimbNoTerm){
        R.push_back("$");
    }//if
    for(int i=0; i<NumReglas; i++){ //Se bysca SimbNoTerm en los lados derechos de cada regla
        //Se recorre la lista del lado derecho buscando al simbolo SimboloNoTerm
        int tam = (int) ArrReglas[i].ListaLadoDerecho.size();
        for(int j=0; j< tam; j++){
            if(ArrReglas[i].ListaLadoDerecho[j].Simbolo == SimbNoTerm){
                ListaPost.clear();
                //Obtenemos la lista que correspondaen a los simbolos que estan despues de SimbNoTerm
                int tam2 = (int)ArrReglas[i].ListaLadoDerecho.size();
                for(int k =j+1; k < tam2; k++){
                    ListaPost.push_back(ArrReglas[i].ListaLadoDerecho.at(k));
                }//for

                //Si no hay más simbolos después de SimbNoTerm, se calcula el Follow del lado izquierdo de la regla
                if(ListaPost.empty()){
                    //Si el simbolo del lado izquierdo es igual al simbolo del que queremos calcular
                    //el follow, omitimos la regla
                    if(!(ArrReglas[i].InfSimbolo.Simbolo == SimbNoTerm)){
                        for(std::string s: Follow(ArrReglas[i].InfSimbolo.Simbolo)){
                            if(R.empty() || !contain(R,s)){
                                R.push_back(s);
                            }
                        }//for
                    }//if
                    break;
                }//if

                //Se calcula el First de la lista l que está despues del elemento j
                Aux.clear();
                Aux = First(ListaPost);
                if(contain(Aux,"epsilon")){
                    Aux.erase(Aux.begin()+WhereIS_contain(Aux,"epsilon"));
                    for(std::string c: Aux){
                        if(R.empty() || !contain(R,c)){
                                R.push_back(c);
                            }
                    }//for

                    if(!(ArrReglas[i].InfSimbolo.Simbolo == SimbNoTerm)){
                        for(std::string s: Follow(ArrReglas[i].InfSimbolo.Simbolo)){
                            if(R.empty() || !contain(R,s)){
                                R.push_back(s);
                            }
                        }//for
                    }//if
                }else{
                    for(std::string c: Aux){
                            if(R.empty() || !contain(R,c)){
                                R.push_back(c);
                            }
                    }//for
                }//if

            }//if
        }//for
    }//for
    return R;
}


DescRecGram_Gram::~DescRecGram_Gram(){
    //dtor
}
