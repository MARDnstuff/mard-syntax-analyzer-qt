#include "AnalizadorLL1.h"

//Funciones auxiliares


int IndexOf(std::string *arr,int tam_arr,std::string simbolo){
    for(int i=0; i<tam_arr; i++){
        if(arr[i] == simbolo){
            return i;
        }//for
    }//for
    return -1;
}

int IndexOf_(int *arr,int tam_arr,int token){
    for(int i=0; i<tam_arr; i++){
        if(arr[i] == token){
            return i;
        }//for
    }//for
    return -1;
}

bool contain_ (std::vector<std::string> n1 , std::string cadena){
    for(std::string s: n1){
        if(cadena == s){
            return true;
        }//if
    }//for
    return false;
}

AnalizadorLL1::AnalizadorLL1(){
//ctor
}

//Constructor por gramatica y nombre del archivo del AFD
 AnalizadorLL1::AnalizadorLL1(std::string CadGramatica, std::string ArchAFDLexic){
    Gram = CadGramatica;
    DescRecG = DescRecGram_Gram(CadGramatica,AFDFile_);
    AFD p = AFD();
    p.Carga_TablaAFD(ArchAFDLexic);
    AnalizLexico p2 = AnalizLexico("",p);
    LexGram = p2;
}
//Constructor por gramatica
 AnalizadorLL1 ::AnalizadorLL1(std::string CadGramatica){
    Gram = CadGramatica;
    DescRecG = DescRecGram_Gram(CadGramatica,AFDFile_);
 }

//Establece el archivo del que se saca el Analizador lexico
void AnalizadorLL1 :: SetLexico(std::string ArchAFDLexic ){
    AFD p = AFD();
    p.Carga_TablaAFD(ArchAFDLexic);
    AnalizLexico p2 = AnalizLexico("",p);
    LexGram = p2;
}

//Crea Tabla LL1
void AnalizadorLL1 :: CrearTablaLL1(){
    std::vector<std::string> ResultFirst;
    std::vector<std::string> ResultFollow;

    if(!DescRecG.AnalizarGramatica()){
       perror("Gramatica erronea"); exit(-1);
    }//if
        DescRecG.IdentificarTerminales();

    int tam_Vt = (int) DescRecG.Vt.size();
    int tam_Vn = (int) DescRecG.Vn.size();
    row = tam_Vn + 1;
    column = tam_Vt + 1 ;

    Vt = new SimbTerm[tam_Vt + 1]; //Numero de columnas de la tabla LL1
    Vt2 = new std::string[tam_Vt + 1]; //Arreglo de terminales para asocialos a las columnas dela tabla LL1
    Vn = new std::string[tam_Vn + 1];//Número de filas de la tabla LL1
    int j=0;
    for(ClaseNodo s: DescRecG.Vt){
        Vt[j] = SimbTerm(s.Simbolo,-1); //falta el token
        Vt2[j] = s.Simbolo;
        j++;
    }//for
    Vt[j] = SimbTerm("$",-1);
    Vt2[j++] = "$";

    j=0;
    for(ClaseNodo s: DescRecG.Vn){
        Vn[j++] = s.Simbolo;
    }//for
    Vn[j++] = "$";
    //Incializacion de la matriz

    TablaLL1 = new int*[tam_Vn + 1];
    for(int i=0; i<tam_Vn+1; i++){
        TablaLL1[i] = new int[tam_Vt+1];
    }//for

    for(int k=0; k<= tam_Vn;k++){
        for(int h=0; h<= tam_Vt;h++){
            TablaLL1[k][h] = -1;
        }//for
    }//for
    int renglon;
    int columna;

    //Se analiza cada una de las reglas y sen colcando las acciones en el renglon que le toca
    for(int NumRegla = 0; NumRegla < DescRecG.NumReglas; NumRegla++){
        renglon = IndexOf(Vn,tam_Vn+1,DescRecG.ArrReglas[NumRegla].InfSimbolo.Simbolo);
        ResultFirst = DescRecG.First(DescRecG.ArrReglas[NumRegla].ListaLadoDerecho);
        for(std::string s: ResultFirst){
            columna = IndexOf(Vt2,tam_Vt+1,s);
            if(columna >= 0){
                TablaLL1[renglon][columna] = NumRegla + 1;
            }//if
        }//for
        //Si hay epsilon en el first, se calcula el follow del lado izquierdo
        if(contain_(ResultFirst,"epsilon")){
            ResultFollow = DescRecG.Follow(DescRecG.ArrReglas[NumRegla].InfSimbolo.Simbolo);
            for(std::string s : ResultFollow){
                columna = IndexOf(Vt2,tam_Vt+1,s);
                TablaLL1[renglon][columna] = NumRegla+1;
            }//for

        }//if

    }//for

}

//Analisador sintactico LL1
bool AnalizadorLL1 :: AnalizSintacLL1(std::string Sigma){
    int Tok, TokTerm;
    int renglon, columna;
    std::stack<Simb> Pila;
    std::stack<Simb> Pila2;
    Simb simbolo, elemPila;
    std::string  CadenaAnaliz = Sigma;
    LexGram.SetSigma(Sigma);
    int Accion;

    simbolo = Simb(Vn[0],false,-1);
    Pila.push(simbolo);
    Tok = LexGram.yylex();

    do{
       if(Pila.empty() && Tok == 0){
            //Cadena sintácticamente correcta
            return true;
       }else if(Pila.empty() && Tok > 0){
            return false;
       }
       elemPila = Pila.top();
       Pila.pop();
       if(elemPila.Terminal){
            if(elemPila.Token == Tok){
                //Pedir otro token. Continuar con el análisis
                Tok = LexGram.yylex();
                continue;
            }else{
                //ERROR: Cadena sintácticamente incorrecta
                return false;
            }//if

       }else{ //El elemento de la Pila es un No terminal
            renglon = IndexOf(Vn,row,elemPila.cadena); //Renglon de la tabla

            //Arreglo de token asociados Vt3
            columna = IndexOf_(Vt3,column,Tok);

            Accion = TablaLL1[renglon][columna];
            //flag2 = Accion; return true;
            if(Accion != -1){ //Accion representa el número de regla
                for(ClaseNodo n: DescRecG.ArrReglas[Accion - 1].ListaLadoDerecho){
                    TokTerm = -1;

                    if(n.Simbolo == "epsilon"){
                        continue;
                    }//if

                    if(n.Terminal){
                        int ind = IndexOf(Vt2,column,n.Simbolo);
                        if(ind < 0){
                            return false;
                        }//if
                        TokTerm = Vt3[ind];
                    }//if
                        simbolo = Simb(n.Simbolo,n.Terminal,TokTerm);
                        Pila2.push(simbolo);
                }//for
                while(!Pila2.empty()){
                        Pila.push(Pila2.top());
                        Pila2.pop();
                }//while

                //flag = Pila.top().cadena; return true;
            }else{
                return false;
            }//if
       }//if
    }while(true);

}

AnalizadorLL1::~AnalizadorLL1()
{
    //dtor
}
