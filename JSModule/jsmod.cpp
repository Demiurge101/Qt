#include "jsmod.h"

JsMod::JsMod()
{
    jsBase = new QJSEngine();
}

JsMod::~JsMod()
{
    delete jsBase;
}


bool JsMod::CalcFormula(QString formula, QVariant* varResult)
{
    if(varResult != nullptr){
        QJSValue ResultJsVar = jsBase->evaluate(formula);
        if(ResultJsVar.isNumber()){
            double val = ResultJsVar.toNumber();
            if(!qIsNaN(val) && !qIsInf(val)){
                varResult->setValue(val);
                return true;
            }
        }
        return false;
    }
    return false;
}

bool JsMod::CalcFormula(QString formula, Variable *varResult)
{
    if(varResult != nullptr){
        QJSValue ResultJsVar = jsBase->evaluate(formula);
        if(ResultJsVar.isNumber()){
            double val = ResultJsVar.toNumber();
            if(!qIsNaN(val) && !qIsInf(val)){
                varResult->setvalue(val);
                return true;
            }
        }
        return false;
    }
    return false;
}

bool JsMod::AddVar(QString name, QVariant *var)
{
    if(var != nullptr){
        QJSValue val = var->toDouble();
        if(val.isNumber()){
                if(!qIsNaN(val.toNumber()) && !qIsInf(val.toNumber())){
                jsBase->globalObject().setProperty(name, val);
                varVec.append(name);
                return true;
            }
        }
        return false;
    }
    return false;
}

bool JsMod::AddVar(Variable *var)
{
    if(var != nullptr){
        QJSValue val = jsBase->newQObject(var);
        jsBase->globalObject().setProperty(var->getname(), val);
        //val.setProperty("значение", 77);
        varVec.append(var->getname());
        //connect(var, Variable::valueChanged, this, JsMod::slotUpdateVar, Qt::ConnectionType::DirectConnection);
        return true;
    }
    return false;
}

bool JsMod::UpdateVar(QString name, QVariant *var)
{
    if(jsBase->globalObject().hasProperty(name)){
        QJSValue temp = var->toDouble();
        if(temp.isNumber()){
            if(!qIsNaN(temp.toNumber()) && !qIsInf(temp.toNumber())){
            jsBase->globalObject().setProperty(name,temp);
            return true;
            }
        }
        return false;
    }
    return false;
}

void JsMod::slotUpdateVar(Variable *var)
{
    if(jsBase->globalObject().hasProperty(var->getname())){
        QJSValue temp = var->getvalue();
        if(temp.isNumber()){
            if(!qIsNaN(temp.toNumber()) && !qIsInf(temp.toNumber())){
            jsBase->globalObject().setProperty(var->getname(),temp);
            }
        }
    }
}

bool JsMod::RemoveVar(QString name)
{
    if(jsBase->globalObject().deleteProperty(name)){
        varVec.remove(varVec.indexOf(name));
        return true;
    }
    return false;

}

bool JsMod::RemoveVar(Variable *var)
{
    if(jsBase->globalObject().deleteProperty(var->getname())){
        varVec.remove(varVec.indexOf(var->getname()));
        return true;
    }
    return false;
}

Variable::Variable(QString name, double value)
{
    _name = name;
    _value = value;
}

QString Variable::getname()
{
    return _name;
}

void Variable::setname(QString val)
{
    _name = val;
}

double Variable::getvalue()
{
    return _value;
}

void Variable::setvalue(double val)
{
    _value = val;
    emit valueChanged(this);
}


