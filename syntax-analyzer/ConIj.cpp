#include "ConIj.h"

//FUNCIONES AUXILIARES
//Verifica que se encuentre el elemento dentro del arreglo
bool ContieneElem_(std::vector<Estado> Conjunto,int IdEdo){
    int tam = (int) Conjunto.size();
    for(int i=0; i<tam;i++){
        if(IdEdo == Conjunto.at(i).get_IdEstado()){
            return true;
        }//if
    }//for
    return false;
}


//--METODOS CLASE ConIj

//Constructor
ConIj::ConIj(){
    Id = -1;
    Edos.clear();
    Acept = false;
    Token=-1;
}


 //Regresa el Id del Conjunto Ij
int ConIj:: get_ConIj_ID (){
    return Id;
}

//Establece el ID del Conjunto Ij
void ConIj:: set_ConIj_ID (int ID){
    Id = ID;
    return;
}

//Regresa el conjunto de estados asociados al Conjunto Ij
std::vector<Estado> ConIj:: get_ConIj_Edos (){
    return Edos;
}

//Añade un Estado al conjunto de estados asoicados al Conjunto Ij
void ConIj:: set_Element_ConIJ(Estado e){
    Edos.push_back(e);
    return;
}

//Establece por completo el conjunto de estados asosicados al Conjunot Ij
void ConIj:: set_ConIJ_Edos(std::vector<Estado> e){
    Edos = e;
    return;
}

//Regresa true si el Conjunto se encuentra ya en el arreglo
//e elementos a buscar en S
int ConIj:: equals_to (std::vector<ConIj> S,std::vector<Estado> e){
    int tam = (int) S.size(),tam_ = (int) e.size();
    int flag=0;
    int tam_Scon;
    for(int i=0; i<tam;i++){
        tam_Scon = (int) S.at(i).get_ConIj_Edos().size();
        if(tam_== tam_Scon){
            for(int j=0; j<tam_;j++){
                if(ContieneElem_(S.at(i).get_ConIj_Edos(),e.at(j).get_IdEstado())){
                    flag++;
                    continue;
                }else{
                    flag=0;
                    break;
                }
            }//for
            if(flag == tam_){ return i;}
        }//if
    }//for
    return -1;
}



