#ifndef JSMOD_H
#define JSMOD_H

#include <QJSEngine>
#include <QJSValue>
#include <QVariant>
#include <QVector>

class Variable;

class JsMod : public QObject
{
    Q_OBJECT
public:
    JsMod();
    ~JsMod();
    bool CalcFormula(QString formula, QVariant* varResult);
    bool CalcFormula(QString formula, Variable* varResult);
    bool AddVar(QString name, QVariant* var);
    bool AddVar(Variable* var);
    bool UpdateVar(QString name, QVariant* var);
    bool RemoveVar(QString name);
    bool RemoveVar(Variable* var);
    QVector<QString> getVectorVars(){ return varVec;}

public slots:
    void slotUpdateVar(Variable* var);
private:
    QJSEngine* jsBase;
    QVector<QString> varVec;



};

class Variable : public QObject
{
    Q_OBJECT
public:
    Variable(){}
    Variable(QString name, double value){_name = name; _value = value;}
    ~Variable(){}

    QString getname();
    void setname(QString val);

    double getvalue();
    void setValue(double val);


    Variable& operator=(const double& rvalue){
        _value = rvalue;
        emit valueChanged(this);
        return *this;
    }

signals:
    void valueChanged(Variable* var);

private:
    QString _name;
    double _value;
};

#endif // JSMOD_H
