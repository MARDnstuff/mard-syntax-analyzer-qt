#ifndef CLASENODO_H
#define CLASENODO_H
#include <string>

class ClaseNodo{
    public:
        std::string Simbolo;
        bool Terminal;
    public:
        ClaseNodo();
        ClaseNodo(std::string Simb);
        ClaseNodo(std::string Simb, bool EsTerminal);
        virtual ~ClaseNodo();

};

#endif // CLASENODO_H
