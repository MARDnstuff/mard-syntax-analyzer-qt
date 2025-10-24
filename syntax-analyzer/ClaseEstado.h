#ifndef CLASEESTADO_H
#define CLASEESTADO_H
#include <vector>
#include "ClaseTransicion.h"

class Estado{
    public:
        int ContadorIdEstado = 0; //contador para seguir la enumeracion secuencial
        //Conjunto de transiciones del estado
        std::vector<Transicion> Trans1;
    private:
        //Identificador del estado
        int idEstado1;
        //Verificador de Estado de aceptación
        bool EdoAcept1;
        //Token para estados de aceptación (número único)
        int Token1;

    public:
        //Constructor de un estado
        Estado();
        //Constructor de un estado vacio
        Estado Estado_null();
        // Regresa id del estado
        int get_IdEstado();
        // Establece el id del estado
        void set_IdEstado(int id);
        // Regresa el valor True si es un estado de aceptación
        bool is_EdoAcept();
        // Establece el valor a True o False a un estado si es una estado de aceptación
        void set_EdoAcept(bool value);
        // Regresa el valor del Token unico
        int get_Token();
        // Establece el valor del Token (valor único)
        void set_Token(int value);
        // Regresa el conjunto de Transiciones asociadas al estado
        std::vector<Transicion>  get_Trans (){
            return Trans1;
        }
        // Establece el conjunto (o alguna transicion dentro del conjunto) de transiciones
        // Agrega a la lista
        std::vector<Transicion> set_Trans (Transicion value);

        virtual ~Estado();


};

#endif // CLASEESTADO_H
