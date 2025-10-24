#ifndef SIMB_H
#define SIMB_H
#include <string>

class Simb{
    public:
        std::string cadena;
        bool Terminal = false;
        int Token;
    public:
        Simb();
        Simb(std::string Cadena,bool esTerminal, int token);
        virtual ~Simb();
};

#endif // SIMB_H
