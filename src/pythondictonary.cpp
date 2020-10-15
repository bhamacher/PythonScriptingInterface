#include "pythondictonary.h"
#include "PythonBinding.h"
#include "generalHelpers.h"
using namespace zPyInt;

PythonDictonary::PythonDictonary(): m_forceType(true)
{

}

PythonDictonary::~PythonDictonary()
{
    Py_DECREF(m_pDict);
}

PyObject *PythonDictonary::value(const QString &p_key)
{
    if(m_pDict!=NULL){
        m_pVal = PyDict_GetItemString(m_pDict, p_key.toUtf8());
        if(CheckType(p_key,m_pVal)){
            return m_pVal;
        }
    }
    return nullptr;
}

bool PythonDictonary::insert(const QString &p_key, PyObject *p_value)
{
    if(m_pDict!=NULL){
        if(CheckType(p_key,p_value)){
            PyDict_SetItemString(m_pDict, p_key.toUtf8(), p_value);
            return true;
        }
    }
    return false;
}

void PythonDictonary::remove(const QString &p_key)
{
    if(m_pDict!=NULL){
        if(0 == PyDict_DelItemString(m_pDict, p_key.toUtf8())){
            typeMap.remove(p_key);
        }
    }
}

void PythonDictonary::clear()
{
  if(m_pDict!=NULL){
    PyDict_Clear(m_pDict);
  }
}

PythonDictonary &PythonDictonary::operator=(const PythonDictonary& dict)
{
    this->cval = dict.cval;
    this->m_name=dict.m_name;
    this->m_pVal=dict.m_pVal;
    this->typeMap=dict.typeMap;
    this->m_pDict=dict.m_pDict;
    Py_INCREF(m_pDict);
    return *this;
}

PyObject* PythonDictonary::operator[](const QString &key)
{
    return value(key);
}


bool PythonDictonary::CheckType(const QString &p_key,PyObject* p_value)
{
    bool ret=true;
    if(m_forceType){
        ret=false;
        if(typeMap.contains(p_key)){
            if(typeMap[p_key] == p_value->ob_type->tp_name){
                ret=true;
            }
        }else{
            typeMap[p_key]=p_value->ob_type->tp_name;
            ret=true;
        }
        if(ret == false){
            throw std::runtime_error(QString("unexpected type in python ").append(m_name).append(".").append(p_key).append(" ").append(p_value->ob_type->tp_name).append(" instead of ").append(typeMap[p_key]).toUtf8());
        }
    }
    return ret;
}

bool PythonDictonary::forceType() const
{
    return m_forceType;
}

void PythonDictonary::setForceType(bool forceType)
{
    m_forceType = forceType;
}
