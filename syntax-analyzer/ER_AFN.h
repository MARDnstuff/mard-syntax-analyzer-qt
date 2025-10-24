#ifndef ER_AFN_H
#define ER_AFN_H
#include <string>
#include "ClaseAFN.h"
#include "AnalizLexico.h"
#include <memory>
class ER_AFN{
    private:
        std::string ExprRegular;

    public:
        int ContarEdo = 0;
        AFN result;
        AnalizLexico L;
    public:
        //Constructor
        ER_AFN(std::string sigma, AFD AutFD);
        //Establece la expresion regular
        void SetExpresion(std::string sigma);
        //Destructor
        virtual ~ER_AFN();
        ////////PROCESO DE EVALUACION//////////
        bool F(std::shared_ptr<AFN> f_ap);
        bool Cp(std::shared_ptr<AFN> f_ap);
        bool C(std::shared_ptr<AFN> f_ap);
        bool Tp(std::shared_ptr<AFN> f_ap);
        bool T(std::shared_ptr<AFN> f_ap);
        bool Ep(std::shared_ptr<AFN> f_ap);
        bool E(std::shared_ptr<AFN> f_ap);
        bool IniConversion();
        ///////////////////////////////////////

};

#endif // ER_AFN_H
