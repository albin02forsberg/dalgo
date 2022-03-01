#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "token.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_input_textChanged(const QString &arg1);

    void on_checkImplicitEqual_stateChanged(int arg1);

    void on_actionragnarsTest_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Token> tokensFromString(const std::string &str);
    void showTokens(const std::vector<Token> &vecOfTokens);
    void showStackOfValues(const std::vector<float> &stackOfValues);
    void showStackOfOperators(const std::vector<char> &stackOfOperators);
    bool isLegalChar(QChar ch);
    void setColorsFromOk(bool ok);
};

#endif // MAINWINDOW_H
