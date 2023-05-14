#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    JsMod* module;
    module = new JsMod();
    QVariant* res = new QVariant();
    Variable* AX = new Variable("Давл1", 45);
    Variable* BX = new Variable("Давл2", 15);
    module->AddVar(AX);
    module->AddVar(BX);
    module->CalcFormula("Давл1 + Давл2", res);
    qDebug() << res->toString();
    *AX = 22;
    *BX = 13;
    module->CalcFormula("Давл1 + Давл2", res);
    qDebug() << res->toString();
    return a.exec();
}
