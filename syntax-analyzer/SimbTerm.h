#ifndef SIMBTERM_H
#define SIMBTERM_H
#include<string>

class SimbTerm{
    public:
        std::string Simbolo;
        int ValToken;
    public:
        SimbTerm();
        SimbTerm(std::string Simb, int Token);
        virtual ~SimbTerm();

};

#endif // SIMBTERM_H
