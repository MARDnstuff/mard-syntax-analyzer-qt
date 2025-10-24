#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
#include "ClaseAFN.h"
#include "ClaseAFD.h"
#include "AnalizLexico.h"


//#include "ConIj.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void CreaBasico();
    void Actualizar_lista();
    void Union();
    void Concatenar();
    void CerraduraMAS();
    void CerraduraKl();
    void Opcional();
    void setTable1();
    void UnionEspecial();
    void ConvAFNaAFD();
    void verAFD();
    void GuardarAFD();
    void CargaAFD();
    void Btn_AnalizLexic();
    void CrearER_AFN();
    void IniciarCalcu();

signals:
    void listUpdated();
    void UnionEspecial_update();
    void ConvAFD_update();


private:
    Ui::Widget *ui;
    int contador = 0;
    unsigned int ID_counter = 1;
    unsigned int ID_counter_AFD = 1;
    std::map<unsigned int, AFN> lista_AFN;
    std::map<unsigned int, AFD> lista_AFD;
    AFD automata_actual;
    //bool AFD_fromFile = false;
};
#endif // WIDGET_H
