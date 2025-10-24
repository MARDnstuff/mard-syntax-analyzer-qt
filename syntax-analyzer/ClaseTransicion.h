#ifndef CLASETRANSICION_H
#define CLASETRANSICION_H


class Transicion{
    private:
    //Variables para rangos de caracteres
        //Simbolo inferior
        char SimbInf1;
        //Simbolo superior
        char SimbSup1;
        //Identificador del Estado al que se puede mover (destino)
        int idEdo_destino;
        //Identificador del Estado origen
        int idEdo_origen;
    public:
        // Constructor para un solo simbolo
        Transicion(char simb, int idEdo_o, int idEdo_d);
        // Constructor para un rango de simbolos
        Transicion (char simb1, char simb2, int idEdo_o ,int idEdo_d);
        // Constructor sin transición
        Transicion();
        // Establece Transición para un solo simbolo
        void set_Transicion(char s1,int idEdo_o ,int idEdo_d);
        // Establece Transición por rango
        void set_Transicion_r(char s1,char s2, int idEdo_o ,int idEdo_d);
        // Regresa el Simbolo inferior
        char get_SimbInf ();
        // Establece el Simbolo inferior
        void set_SimbInf (char value);
        // Regresa el Simbolo superior
        char get_SimbSup ();
        // Establece el Simbolo superior
        void set_SimbSup (char value);
        // Regresa el estado al que tiene transición con el caracter S
        int get_EdoTrans (char simb);
        // Establece el estado origen
        void set_EdoOrigen (int idEdo_o);
        // Regresa el estado origen
        int get_EdoOrigen ();
        // Establece el estado destino
        void set_EdoDestino (int idEdo_d);
        // Regresa el estado destino
        int get_EdoDestino ();

        virtual ~Transicion();
};



#endif // CLASETRANSICION_H
