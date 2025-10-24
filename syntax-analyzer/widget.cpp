#include "widget.h"
#include "./ui_widget.h"
#include "ClaseAFN.h"
#include "ER_AFN.h"
#include "EvaluadorExp1.h"

#include <QDebug>
#include <QMessageBox>
#include <QCheckBox>
#include <QFile>
#include <QFileDialog>

typedef struct Nodo {
    unsigned int ID;
    unsigned int Token;
}Data_;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //ComboBox (listas AFN)
    connect(this, &Widget::listUpdated, this, &Widget::Actualizar_lista);
    connect(this, &Widget::UnionEspecial_update, this, &Widget::Actualizar_lista);

    //Basico
    connect(ui->pushButton_CrearAFN, &QPushButton::clicked, this, &Widget::CreaBasico);

    //Union
    connect(ui->pushButton_Union, &QPushButton::clicked, this, &Widget::Union);

    //Concatenar
    connect(ui->pushButton_Conca, &QPushButton::clicked, this, &Widget::Concatenar);

    //Cerradura +
    connect(ui->pushButton_CerrMAS, &QPushButton::clicked, this, &Widget::CerraduraMAS);

    //Cerradura *
    connect(ui->pushButton_Kleene, &QPushButton::clicked, this, &Widget::CerraduraKl);

    //Opcional ?
    connect(ui->pushButton_Opcional, &QPushButton::clicked, this, &Widget::Opcional);

    //Tabla Union Especial
    ui->pushButton_UnirEsp->setDisabled(true);
    connect(this, &Widget::listUpdated, this, &Widget::setTable1);
    connect(ui->pushButton_UnirEsp, &QPushButton::clicked, this, &Widget::UnionEspecial);

    //Convertir AFN a AFD
    ui->pushButton_ConvertirAFN->setDisabled(true);
    connect(this, &Widget::UnionEspecial_update, this, [&](){ui->pushButton_ConvertirAFN->setDisabled(false); });
    connect(ui->pushButton_ConvertirAFN, &QPushButton::clicked, this, &Widget::ConvAFNaAFD);

    //Ver AFD
    ui->pushButton_verAFD->setDisabled(true);
    connect(ui->pushButton_verAFD, &QPushButton::clicked, this, &Widget::verAFD);
    connect(this, &Widget::ConvAFD_update, this, [&](){ui->pushButton_verAFD->setDisabled(false);});
    connect(this, &Widget::ConvAFD_update, this, &Widget::Actualizar_lista);

    //Guardar AFD
    ui->toolButton_Guardar->setDisabled(true);
    connect(ui->toolButton_Guardar, &QToolButton::clicked, this, &Widget::GuardarAFD);
    connect(this, &Widget::ConvAFD_update, this, [&](){ui->toolButton_Guardar->setDisabled(false); });

    //Cargar AFD
    connect(ui->toolButton_CargaAFD, &QToolButton::clicked, this, &Widget::CargaAFD);

    //Analizador Lexico
    connect(ui->pushButton_UsarLexic, &QPushButton::clicked, this, &Widget::Btn_AnalizLexic);

    //ER a AFN
    ui->pushButton_CreaER->setDisabled(true);
    connect(ui->pushButton_CreaER, &QPushButton::clicked, this, &Widget::CrearER_AFN);

    //Calcu
    ui->pushButton_IniciarEval->setDisabled(true);
    connect(ui->pushButton_IniciarEval, &QPushButton::clicked, this, &Widget::IniciarCalcu);


}

Widget::~Widget(){
    delete ui;
}

//Crea automata Basico
void Widget::CreaBasico(){
    std::cout << "Creando AFN Basico" <<std::endl;

    if(ui->lineEdit_Simb2->text().isEmpty() && ui->lineEdit_Simb->text().isEmpty() || ui->lineEdit_Simb2->text().isEmpty() || ui->lineEdit_Simb->text().isEmpty()){
        QString msg = "Texto vacio";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }
    char c1 = ui->lineEdit_Simb->text().toStdString().at(0);
    char c2 = ui->lineEdit_Simb2->text().toStdString().at(0);

    AFN automata = AFN();
    AFN a1;
    a1 = automata.AFN_Basico(c1,c2,this->contador);
    a1.IdAFN = this->ID_counter;
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(this->ID_counter,a1));
    a1.Mx_Adyacencia(a1);
    this->ID_counter++;
    this->contador = a1.get_Contador();

    emit listUpdated();

    //House keeping
    ui->lineEdit_Simb->clear();
    ui->lineEdit_Simb2->clear();

    //Display message
    QString msg = "Automata creado : )";
    QMessageBox::information(this, "Info Message", msg);

//    for(int i =1; i <= this->lista_AFN.size(); i++){
//        qDebug() << this->lista_AFN.at(i).IdAFN;
//    }
}

void Widget::Actualizar_lista(){
    qDebug() << Q_FUNC_INFO;
    ui->comboBox_AFNs->clear();
    ui->comboBox_AFNs2->clear();
    ui->comboBox_AFNs3->clear();
    ui->comboBox__AFNs4->clear();
    ui->comboBox_AFNs5->clear();
    ui->comboBox_AFNs6->clear();
    ui->comboBox_AFNs7->clear();
    ui->comboBox_AFNs8->clear();
    ui->comboBox_AFDs1->clear();

    for(int i = 1; i <= this->lista_AFN.size() ;i++){
        QString  s = QString::number(this->lista_AFN.at(i).IdAFN) + " - AFN simb: " +
                this->lista_AFN.at(i).Alfabeto.at(0) + "-" + this->lista_AFN.at(i).Alfabeto.at(this->lista_AFN.at(i).Alfabeto.size() - 1);

        ui->comboBox_AFNs->addItem(s);
        ui->comboBox_AFNs2->addItem(s);
        ui->comboBox_AFNs3->addItem(s);
        ui->comboBox__AFNs4->addItem(s);
        ui->comboBox_AFNs5->addItem(s);
        ui->comboBox_AFNs6->addItem(s);
        ui->comboBox_AFNs7->addItem(s);
        ui->comboBox_AFNs8->addItem(s);
    }//for

    qDebug() << this->lista_AFD.size();
    QString  s;
    for(int i = 1; i <= this->lista_AFD.size() ;i++){
        s = QString::number(this->lista_AFD.at(i).get_IdAFD()) + " - AFD";
        ui->comboBox_AFDs1->addItem(s);
    }//for


}

//Une dos automatas
void Widget::Union(){
    qDebug() << Q_FUNC_INFO;
    qDebug() <<"usuario:" <<ui->comboBox_AFNs->currentText() <<":: ID: " << ui->comboBox_AFNs->currentIndex();

    if(ui->comboBox_AFNs->currentIndex() == -1){
        //Display message
        QString msg = "No hay automatas";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }//if

    unsigned int ID_automata1 = ui->comboBox_AFNs->currentIndex() + 1;
    unsigned int ID_automata2 = ui->comboBox_AFNs2->currentIndex() + 1;

    AFN automata1 = this->lista_AFN.at(ID_automata1);
    AFN automata2 = this->lista_AFN.at(ID_automata2);
    automata1 = automata1.AFN_Union(automata2);
    automata1.IdAFN = this->ID_counter;
    this->ID_counter++;
    this->contador = automata1.get_Contador();

    //Agregamos a la lista
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(automata1.IdAFN,automata1));
    automata1.Mx_Adyacencia(automata1);

    QString msg = "Se Unieron correctamente los automatas : )";
    QMessageBox::information(this, "Info Message", msg);
    emit listUpdated();
}

//Concatena dos automatas
void Widget::Concatenar(){
    qDebug() << Q_FUNC_INFO;
    qDebug() <<"usuario:" <<ui->comboBox_AFNs3->currentText() <<":: ID: " << ui->comboBox_AFNs3->currentIndex();

    if(ui->comboBox_AFNs3->currentIndex() == -1){
        //Display message
        QString msg = "No hay automatas";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }//if

    unsigned int ID_automata1 = ui->comboBox_AFNs3->currentIndex() + 1;
    unsigned int ID_automata2 = ui->comboBox__AFNs4->currentIndex() + 1;

    AFN automata1 = this->lista_AFN.at(ID_automata1);
    AFN automata2 = this->lista_AFN.at(ID_automata2);
    automata1 = automata1.AFN_Conca(automata2);
    automata1.IdAFN = this->ID_counter;
    this->ID_counter++;
    this->contador = automata1.get_Contador();

    //Agregamos a la lista
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(automata1.IdAFN,automata1));
    automata1.Mx_Adyacencia(automata1);

    QString msg = "Se Concatenaron correctamente los automatas : )";
    QMessageBox::information(this, "Info Message", msg);
    emit listUpdated();
}

//Aplicala la cerradura +
void Widget::CerraduraMAS(){
    qDebug() << Q_FUNC_INFO;
    qDebug() <<"usuario:" <<ui->comboBox_AFNs5->currentText() <<":: ID: " << ui->comboBox_AFNs5->currentIndex();

    if(ui->comboBox_AFNs5->currentIndex() == -1){
        //Display message
        QString msg = "No hay automatas";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }//if

    unsigned int ID_automata1 = ui->comboBox_AFNs5->currentIndex() + 1;

    AFN automata1 = this->lista_AFN.at(ID_automata1);
    automata1 = automata1.AFN_CerrPOS();
    automata1.IdAFN = this->ID_counter;
    this->ID_counter++;
    this->contador = automata1.get_Contador();

    //Agregamos a la lista
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(automata1.IdAFN,automata1));
    automata1.Mx_Adyacencia(automata1);

    QString msg = "Se Cerradura+ correctamente los automatas : )";
    QMessageBox::information(this, "Info Message", msg);
    emit listUpdated();
}

void Widget::CerraduraKl(){
    qDebug() << Q_FUNC_INFO;
    qDebug() <<"usuario:" <<ui->comboBox_AFNs6->currentText() <<":: ID: " << ui->comboBox_AFNs6->currentIndex();

    if(ui->comboBox_AFNs6->currentIndex() == -1){
        //Display message
        QString msg = "No hay automatas";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }//if

    unsigned int ID_automata1 = ui->comboBox_AFNs6->currentIndex() + 1;

    AFN automata1 = this->lista_AFN.at(ID_automata1);
    automata1 = automata1.AFN_CerrKleene();
    automata1.IdAFN = this->ID_counter;
    this->ID_counter++;
    this->contador = automata1.get_Contador();

    //Agregamos a la lista
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(automata1.IdAFN,automata1));
    automata1.Mx_Adyacencia(automata1);

    QString msg = "Se aplico Kleene correctamente los automatas : )";
    QMessageBox::information(this, "Info Message", msg);
    emit listUpdated();
}

void Widget::Opcional(){
    qDebug() << Q_FUNC_INFO;
    qDebug() <<"usuario:" <<ui->comboBox_AFNs7->currentText() <<":: ID: " << ui->comboBox_AFNs7->currentIndex();

    if(ui->comboBox_AFNs7->currentIndex() == -1){
        //Display message
        QString msg = "No hay automatas";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }//if

    unsigned int ID_automata1 = ui->comboBox_AFNs7->currentIndex() + 1;

    AFN automata1 = this->lista_AFN.at(ID_automata1);
    automata1 = automata1.AFN_Opcional();
    automata1.IdAFN = this->ID_counter;
    this->ID_counter++;
    this->contador = automata1.get_Contador();

    //Agregamos a la lista
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(automata1.IdAFN,automata1));
    automata1.Mx_Adyacencia(automata1);

    QString msg = "Se aplico Opcional ? correctamente a los automatas : )";
    QMessageBox::information(this, "Info Message", msg);
    emit listUpdated();

}

void Widget::setTable1(){
        ui->pushButton_UnirEsp->setDisabled(false);
        qDebug() << Q_FUNC_INFO;

        int tam = this->lista_AFN.size();
        QStringList title = { "CheckBox","ID" ,"Simbolo" ,"Token"};
        ui->Table1->setRowCount(tam);
        ui->Table1->setColumnCount(4);
        ui->Table1->setHorizontalHeaderLabels(title);
        qDebug() << tam;
        for(int j = 0; j < tam; j++){
            QString s = QString::number(this->lista_AFN.at(j+1).IdAFN);
            QString s2 = "vacio";
            QString s3 = QString::fromStdString("")  +
                    this->lista_AFN.at(j+1).Alfabeto.at(0) + "-" + this->lista_AFN.at(j+1).Alfabeto.at(this->lista_AFN.at(j+1).Alfabeto.size() - 1);

            QTableWidgetItem *newItem = new QTableWidgetItem(s);
            QTableWidgetItem *newItem2 = new QTableWidgetItem(s2);
            QTableWidgetItem *newItem3 = new QTableWidgetItem(s3);
            newItem->setTextAlignment(Qt::AlignCenter);
            newItem2->setTextAlignment(Qt::AlignCenter);
            newItem3->setTextAlignment(Qt::AlignCenter);

            //Adding checbox
            QWidget *checkBoxWidget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();
            QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);

            layoutCheckBox->addWidget(checkBox);
            layoutCheckBox->setAlignment(Qt::AlignCenter);  // Center the checkbox
            layoutCheckBox->setContentsMargins(0,0,0,0);

            ui->Table1->setCellWidget(j,0,checkBoxWidget);
            ui->Table1->setItem(j,1,newItem);
            ui->Table1->setItem(j,2,newItem3);
            ui->Table1->setItem(j,3,newItem2);
        }//for

}

//Union especial
void Widget::UnionEspecial(){
    qDebug() << Q_FUNC_INFO;

    QMessageBox msgBox;
    std::vector<Data_> ID_Aselected;
    int tam = ui->Table1->rowCount();

    for(int i = 0; i<tam; i++){

        // Taking the widget from the cell
        QWidget *item = ( ui->Table1->cellWidget(i,0));
        // Taking the widget from the layout and cast it to QCheckBox
        QCheckBox *checkB = qobject_cast <QCheckBox*> (item->layout()->itemAt(0)->widget());

        if(checkB->isChecked()){
            Data_ obj;
            QString s = ui->Table1->item(i,1)->text();
            QString s2 = ui->Table1->item(i,3)->text();
            if(s2 == "vacio"){
                msgBox.setText("Campo vacio, favor de completarlo");
                msgBox.exec();
                return;
            }//if
            obj.ID = s.toInt();
            obj.Token= s2.toInt();
            //std::cout<<p2<<std::endl; //prueba
            ID_Aselected.push_back(obj);
            s.clear();
            s2.clear();
        }//if
    }//for


    int tam_ = (int) ID_Aselected.size();
    if(tam_ <= 0 ){
        msgBox.setText("Ningun automata fue seleccionado");
        msgBox.exec();
        return;
    }

    std::cout<<"------->"<<tam_<<std::endl;
    AFN e = AFN();
    for(int i=0; i< tam_ ; i++){
        AFN e2 = this->lista_AFN.at(ID_Aselected.at(i).ID);
        e.AFN_UnionEspecial(e2,ID_Aselected.at(i).Token,this->contador);
    }//for
    e.IdAFN = this->ID_counter;
    this->ID_counter++;
    e.Mx_Adyacencia(e);
    this->lista_AFN.insert(std::pair<unsigned int, AFN>(e.IdAFN,e));
    msgBox.setText("Union especial realizada");
    msgBox.exec();

    emit UnionEspecial_update();
}

//Convierte un AFN a AFD
void Widget::ConvAFNaAFD(){
    qDebug() << Q_FUNC_INFO;
    unsigned int ID_automata1 = ui->comboBox_AFNs8->currentIndex() + 1;
    qDebug() <<ID_automata1;

    unsigned int ID_AFD = this->ID_counter_AFD;

    //Conversión de automatas
    AFN e = this->lista_AFN.at(ID_automata1);

    if(!e.SeAgregoAFNUnionLexico){
        QString msg = "Automata erroneo (Sin Union Especial)";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }
    this->ID_counter_AFD++;

    std::cout<<"-->"<<e.IdAFN<<std::endl;
    AFD e2 = AFD();
    e2 = e2.Conv_AFNaAFD(e);
    e2.set_IdAFD(ID_AFD);
    e2.Crea_TablaAFD();
    //Agregamos  a lista AFD
    this->lista_AFD.insert(std::pair<unsigned int, AFD>(e2.get_IdAFD(),e2));

    //Este automata creado sera el actual
    this->automata_actual = e2;

    //Tabla
    QStringList title;
    QString c;
    for(unsigned int i=0; i<256; i++){
        c.append((char)i);
        title.push_back(c);
        c.clear();
    }//for

    int tam = (int) e2.get_EdoAFN().size();
    title.push_back("Token");
    ui->Table2->setRowCount(tam);
    ui->Table2->setColumnCount(257);
    ui->Table2->setHorizontalHeaderLabels(title);

    for(int i=0; i<tam;i++){
       for(int j=0; j<257;j++){
           QString s =QString::number(e2.Mx_adyacencia[i][j]);
            QTableWidgetItem *newItem = new QTableWidgetItem(s);
            newItem->setTextAlignment(Qt::AlignCenter);
            ui->Table2->setItem(i,j,newItem);
        }//for
    }//for
    QString  s = QString::number(this->automata_actual.get_IdAFD()) + " - AFD simb: " +
            this->automata_actual.Alfabeto.at(0) + "-" + this->automata_actual.Alfabeto.at(this->automata_actual.Alfabeto.size() - 1);

    ui->label_AFDactual->setText(s);
    emit ConvAFD_update();
}

//Muestra la Tabla correspondiente del AFD seleccionado
void Widget::verAFD(){
    qDebug() << Q_FUNC_INFO;
    ui->pushButton_CreaER->setDisabled(false);
    ui->pushButton_IniciarEval->setDisabled(false);
    ui->Table2->clear();
    this->automata_actual = this->lista_AFD.at(ui->comboBox_AFDs1->currentIndex() + 1);;
    //Tabla
    QStringList title;
    QString c;
    for(unsigned int i=0; i<256; i++){
        c.append((char)i);
        title.push_back(c);
        c.clear();
    }//for

    int tam = this->automata_actual.tamMx_row;

    title.push_back("Token");
    ui->Table2->setRowCount(tam);
    ui->Table2->setColumnCount(257);
    ui->Table2->setHorizontalHeaderLabels(title);

    for(int i=0; i<tam;i++){
        for(int j=0; j<257;j++){
            QString s =QString::number(this->automata_actual.Mx_adyacencia[i][j]);
            QTableWidgetItem *newItem = new QTableWidgetItem(s);
            newItem->setTextAlignment(Qt::AlignCenter);
            ui->Table2->setItem(i,j,newItem);
            //qDebug() << this->automata_actual.Mx_adyacencia[i][j];
        }//for
    }//for

    QString  s = QString::number(this->automata_actual.get_IdAFD()) + " - AFD";

    ui->label_AFDactual->setText(s);
}

//Guarda la tabla del AFD actual en un txt
void Widget::GuardarAFD(){
    qInfo() << this << Q_FUNC_INFO;
    QMessageBox msgBox;
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/Users/mard/Desktop/Proyecto_Compilador/Archivos_AFD", tr("Text files (*.txt)"));
    qDebug() <<fileName;

    if(fileName.isEmpty()){
        QString msg = "Archivo no especificado";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }
    if(this->automata_actual.Guarda_TablaAFD(fileName.toStdString())){
        msgBox.setText("File succesfully saved");
        msgBox.exec();
    }else{
        msgBox.setText("ERROR");
        msgBox.exec();
    }//if
}

//Carga un AFD desde un archivo txt
void Widget::CargaAFD(){
    qInfo() << this << Q_FUNC_INFO;

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/Users/mard/Desktop/Game_Of_Life/Archivos_txt", tr("Text files (*.txt)"));
    if(fileName.isEmpty()){
       QString msg = "Archivo no especificado";
       QMessageBox::warning(this, "Info Message", msg);
        return;
    }

    qDebug() << fileName;
    unsigned int ID_AFD = this->ID_counter_AFD;
    AFD e = AFD();
    e.Carga_TablaAFD(fileName.toStdString());
    e.set_IdAFD(ID_AFD);

    this->ID_counter_AFD++;


    this->lista_AFD.insert(std::pair<unsigned int, AFD>(e.get_IdAFD(),e));


    QString msg = "File uploaded";
    QMessageBox::information(this, "Info Message", msg);
    ui->pushButton_verAFD->setDisabled(false);
    emit listUpdated();

}

//Usar Analizador Lexico (Muestra lexemas)
void Widget::Btn_AnalizLexic(){
    qInfo() << this << Q_FUNC_INFO;
    QString T1 = ui->lineEdit_Lexic->text();
    AnalizLexico a = AnalizLexico(T1.toStdString(),this->automata_actual);

    int n,tam=0;
    while(a.yylex()!= 0){
        tam++;
    }//while

    a.SetSigma(T1.toStdString());
    //Tabla
    QStringList title = { "Lexema", "Token"};
    ui->Table3->setRowCount(tam);
    ui->Table3->setColumnCount(2);
    ui->Table3->setHorizontalHeaderLabels(title);

    for(int j=0; j<tam; j++){
        n = a.yylex();
        std::cout<<a.Lexema<<std::endl;
        QString s = QString::number(n);
        QString s2 = QString::fromStdString(a.Lexema);
        QTableWidgetItem *newItem = new QTableWidgetItem(s);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(s2);
        ui->Table3->setItem(j,0,newItem2);
        ui->Table3->setItem(j,1,newItem);

    }//while

}

//Crear AFN mediante ER
void Widget::CrearER_AFN(){
    qInfo() << this << Q_FUNC_INFO;
    QMessageBox msgBox;
    QString T1 = ui->lineEdit_ERbox->text();

    if(T1.isEmpty()){
        msgBox.setText("ERROR: No hay expresion (on_Btn_CrearAFN_ER_clicked)");
        msgBox.exec();
        return;
    }else{
        std::cout<<T1.toStdString()<<std::endl;
        ER_AFN e = ER_AFN(T1.toStdString(),this->automata_actual);
        e.ContarEdo = this->contador;
        if(e.IniConversion()){
            msgBox.setText("Se ha creado un AFN");
            msgBox.exec();
            e.result.Mx_Adyacencia(e.result);
            e.result.IdAFN = this->ID_counter;
            this->ID_counter++;

            this->lista_AFN.insert(std::pair<unsigned int, AFN>(e.result.IdAFN,e.result));
            this->contador = e.result.get_Contador();
            qDebug() << "CONT: "<< this->contador;
        }else{
            msgBox.setText("ERROR (2): Expresion erronea (on_Btn_CrearAFN_ER_clicked)");
            msgBox.exec();
        }
    }//if
    ui->pushButton_ConvertirAFN->setDisabled(false);
    emit listUpdated();

}

//Inicia la calcu
void Widget::IniciarCalcu(){
    qInfo() << this << Q_FUNC_INFO;
    QString T1 = ui->lineEdit_Calcu->text();
    qDebug() << T1;

    QMessageBox msgBox;
    if(T1.isEmpty()){
        msgBox.setText("ERROR: No hay expresion (on_Btn_CrearAFN_ER_clicked)");
        msgBox.exec();
        return;
    }//if

    EvaluadorExp1 e = EvaluadorExp1(T1.toStdString(), this->automata_actual);
    if(e.IniEval()){
        QString msg = T1 + " = " + QString::number(e.result);
        QMessageBox::information(this, "Info Message", msg);
    }else{
        QString msg = "ERROR: InciarCalcu()";
        QMessageBox::critical(this, "Info Message", msg);
    }//if




}

