#include "pysharedreference.h"

using namespace zPyInt;

PySharedRef::PySharedRef(): m_object(NULL)
{

}

PySharedRef::PySharedRef(PyObject *p_pObj): m_object(p_pObj)
{
    Py_INCREF(m_object);
}

PySharedRef::PySharedRef(const PySharedRef &p_pObj)
{
    this->m_object=p_pObj.m_object;
    Py_INCREF(m_object);
}

PySharedRef::~PySharedRef()
{
    if(m_object != NULL){
        Py_DECREF(this->m_object);
    }
}

PyObject* PySharedRef::data() const
{
    return m_object;
}

PySharedRef PySharedRef::operator=(PyObject *p_pObj)
{
    if(m_object != NULL){
        Py_DECREF(this->m_object);
    }
    this->m_object=p_pObj;
    if(this->m_object != NULL){
        Py_INCREF(this->m_object);
    }
    return *this;
}

PySharedRef &PySharedRef::operator=(const PySharedRef &p_pObj)
{
    if(m_object != NULL){
        Py_DECREF(this->m_object);
    }
    this->m_object=p_pObj.m_object;
    if(this->m_object != NULL){
        Py_INCREF(this->m_object);
    }
    return *this;
}

PyObject *PySharedRef::object() const
{
    return m_object;
}

void PySharedRef::setObject(PyObject *object)
{
    m_object = object;
}
