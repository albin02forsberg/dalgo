#include "mainwindow.h"
#include "token.h"

#include "ui_mainwindow.h"
#include "ragnarstest.h"
#include <QDebug>
#include <vector>
#include <string>
#include <assert.h>
#include <QMessageBox>

#include "studentscalculator.h"


using namespace std;

vector<Token> tokensFromString(const string& str , bool addFinalEqual);



string stringFromFloat(float value, int decimals){
    string str;
    char s[100];
    if (decimals==2)
        std::sprintf(s, "%.2f", value);
    else std::sprintf(s, "%f", value);
    str = s;
    return str;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



/********************************************************************
ANROP:    vecOfTopkens = tokensFromString(   inputString )
VERSION:  071111 RAG
UPPGIFT:  Ett token är antingen ett decimaltal, en operator eller en parantes.
          Rutinen läser inputString och returnerar en vektor med resultatet.
**********************************************************************/
vector<Token> MainWindow::tokensFromString(const string& str)
{
 return ::tokensFromString(str, ui->checkImplicitEqual->isChecked() );
}





void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void MainWindow::showTokens( const vector<Token> &vecOfTokens){

    QBoxLayout *pTokenLayout = dynamic_cast<QBoxLayout*>( ui->stackboxTokens->layout() );
    assert( pTokenLayout != nullptr );

    clearLayout(pTokenLayout);
    for (Token tok : vecOfTokens){
        string str;
        if (tok.m_isValueToken)
            str = stringFromFloat(tok.m_value,2);
        else str = tok.m_opSymbol;
        pTokenLayout->addWidget(new QLabel(str.c_str()));
    }
    pTokenLayout->addStretch();
}

void MainWindow::showStackOfValues( const vector<float> &stackOfValues){

    QBoxLayout *pLayout = dynamic_cast<QBoxLayout*>( ui->stackboxValues->layout() );
    assert( pLayout != nullptr );

    clearLayout(pLayout);
    for (float value : stackOfValues){
        string str = stringFromFloat(value,2);
        pLayout->insertWidget(0,new QLabel(str.c_str()));
    }
    pLayout->addStretch();
}


void MainWindow::showStackOfOperators( const vector<char> &stackOfOperators){

    QBoxLayout *pLayout = dynamic_cast<QBoxLayout*>( ui->stackboxOperators->layout() );
    assert( pLayout != nullptr );

    clearLayout(pLayout);
    for (char op : stackOfOperators){
        string str;
        str = op;
        pLayout->insertWidget(0,new QLabel(str.c_str()));
    }
    pLayout->addStretch();
}

bool MainWindow::isLegalChar(QChar ch){
    static const QString legal(" 0123456789.+-*/^()");

    return legal.contains(ch);
}
void MainWindow::setColorsFromOk(bool ok){
    if (ok){
        ui->input->setStyleSheet("QLineEdit { background-color : white; color : black; }");
    }
    else {
        ui->input->setStyleSheet("QLineEdit { background-color : white; color : red; }");
    }
}

void MainWindow::on_input_textChanged(const QString &arg1)
{    
    string inStr = arg1.toUtf8().constData();


    if ( arg1.length()>0 ){
        QChar lastchar = arg1[arg1.length()-1];
        if (!isLegalChar(lastchar)){
            QString stringReduced = arg1;
            stringReduced.remove(lastchar);
            ui->input->setText( stringReduced );
            return;
        }
    }


    vector<Token> vecOfTokens = tokensFromString(inStr);

    showTokens(vecOfTokens);

    vector<float> vecValues;
    vector<char> vecOp;

    bool ok = applyParsingAlgorithm(vecOfTokens, (vecValues), (vecOp));
    setColorsFromOk(ok);

    showStackOfValues(vecValues);
    showStackOfOperators(vecOp);

    if (vecValues.size()==1 && vecOp.empty()){
        ui->result->setText( QString::fromStdString( stringFromFloat( vecValues.back(),-1) ) );
    }
    else ui->result->setText( "" );

}

void MainWindow::on_checkImplicitEqual_stateChanged(int arg1)
{
    on_input_textChanged( ui->input->text() );
}

void MainWindow::on_actionragnarsTest_triggered()
{
    bool ok = ragnarsTest();
    if (ok) {
        string str = string("Grattis ")
                   + nameOfStudent6() +"! "
                   + "Testen lyckades!";
        QMessageBox::information(this, "ragnarsTest", QString::fromStdString( str ));
    }
    else {
        string str = string("Tyvärr ")
                   + nameOfStudent6() +"! "
                   + "Testen misslyckades!"
                   + " "
                   + stringWithLastError();
        QMessageBox::critical(this, "ragnarsTest", QString::fromStdString(str) );
    }

}
