#ifndef JSMOD_H
#define JSMOD_H

#include <QJSEngine>
#include <QJSValue>
#include <QVariant>
#include <QMap>
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
    //Q_PROPERTY(double value MEMBER _value NOTIFY valueChanged);
    Q_PROPERTY(double value READ getvalue WRITE setvalue);
    Q_PROPERTY(QMap value MEMBER _mapvalues);
public:
    Q_INVOKABLE Variable(){}
    Q_INVOKABLE Variable(QString name, double value);
    Q_INVOKABLE ~Variable(){}

    Q_INVOKABLE QString getname();
    Q_INVOKABLE void setname(QString val);

    Q_INVOKABLE double getvalue();
    Q_INVOKABLE void setvalue(double val);


    Q_INVOKABLE Variable& operator=(const double& rvalue){
        _value = rvalue;
        //emit valueChanged(this);
        return *this;
    }

signals:
    void valueChanged(Variable* var);

public:
     QString _name;
     double _value;
     QMap<QString, QVariant> _mapvalues;
};

#endif // JSMOD_H
