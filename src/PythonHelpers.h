#ifndef PYTHONHEPERS_H
#define PYTHONHEPERS_H

#include <exception>
#include <QList>
#include <QVariant>
#include <QString>
#include "pyhelper.h"
#include "pysharedreference.h"

/**
 * @brief PyListToQList convert pythonlist to QList
 * @param p_obj: The pythonlist object
 * @param p_checkType: true: throws runtime exception if list is of differetn types
 * @return QList
 *
 * @exception runtime_error: python object is not of type list
 * @exception runtime_error: python list is of different types (optional)
 */
namespace zPyInt {
QList<PySharedRef> PyListToQList(PyObject* p_obj,bool p_checkType=false){
    QList<PySharedRef> ret;
    QString type;
    if(QString(p_obj->ob_type->tp_name) != "list"){
        throw std::runtime_error("python object is not of type list");
    }
    for(Py_ssize_t i=0;i<PyList_Size(p_obj);++i){
        if(i == 0){
            type=PyList_GetItem(p_obj,0)->ob_type->tp_name;
        }
        ret.append(PySharedRef(PyList_GetItem(p_obj,i)));
        if(type != PyList_GetItem(p_obj,i)->ob_type->tp_name && p_checkType){
            throw std::runtime_error("python list is of different types");
        }
    }
    return ret;
}

/**
 * @brief PyTupleToQList Conerts tuple to QList
 * @param p_obj: The tuple object
 * @param p_checkType: true: throws runtime exception if list is of different types (optional)
 * @return QList
 *
 * @exception runtime_error: python object is not of type tuple
 * @exception runtime_error: python tuple is of different types (optional)
 */
QList<PySharedRef> PyTupleToQList(PyObject* p_obj,bool p_checkType=false){
    QList<PySharedRef> ret;
    QString type;
    if(QString(p_obj->ob_type->tp_name) != "tuple"){
        throw std::runtime_error("python object is not of type tuple");
    }
    for(Py_ssize_t i=0;i<PyTuple_Size(p_obj);++i){
        if(i == 0){
            type=PyTuple_GetItem(p_obj,0)->ob_type->tp_name;
        }
        ret.append(PySharedRef(PyTuple_GetItem(p_obj,i)));
        if(type != PyTuple_GetItem(p_obj,i)->ob_type->tp_name && p_checkType){
            throw std::runtime_error("python list is of different types");
        }
    }
    return ret;
}

/**
 * @brief PyDeepTupleListToQList Converts any kind of PyObject* into a QList
 * @param p_obj: The PyObject* (should be tuple or list)
 * @param p_checkType: true: throws runtime exception if result list is of different types (optional)
 * @return QList
 *
 * @exception runtime_error: python tuple is of different types (optional)
 *
 * This function takes a Python tuple or list object. and Creates a QList with Python
 * Objects which are not of type tuple or list. It goes as deep as necessary.
 *
 * For exammple:
 *
 * python:
 * @code
 * obj = ([('val1','val2'),'val3',(['val4','val5'],'val7')])
 * @endcode
 * c++ code:
 * (the expression above is equal to the following expression after conversion)
 * @code
 * QList<PySharedRef> list = {'val1', 'val2', 'val3', 'val4', 'val5', 'val6', 'val7'}
 * @endcode
 *
 * Please consider all elements in list are of type PySharedRef and must be converter to
 * a C type before use. e.g PyLong_AsLong(list.at(0).data())
 */

QList<PySharedRef> PyDeepTupleListToQList(PyObject* p_obj,bool p_checkType=false){

    QList<PySharedRef> ret;
    QList<PySharedRef> deepBuf;
    bool itMarker=false;
    QString type;
    ret.append(p_obj); //implicit conversion
    if(QString(ret.last().data()->ob_type->tp_name)== "tuple" || QString(ret.last().data()->ob_type->tp_name) == "list"){
        itMarker=true;
    }
    while(itMarker){
        deepBuf=ret;
        ret.clear();
        itMarker=false;
        for(PySharedRef it : deepBuf){
            if(QString(it.data()->ob_type->tp_name) == "tuple" ){
                ret.append(PyTupleToQList(it.data(),false));
            }else if(QString(it.data()->ob_type->tp_name) == "list"){
                ret.append(PyListToQList(it.data(),false));
            }else{
                ret.append(it);
            }
            if(QString(ret.last().data()->ob_type->tp_name) == "tuple" || QString(ret.last().data()->ob_type->tp_name) == "list"){
                itMarker=true;
            }
        }
    }

    if(p_checkType){
        for(PySharedRef it : ret){
            if(it.data()->ob_type->tp_name != ret.at(0).data()->ob_type->tp_name){
                throw std::runtime_error("python deep list is of different types");
            }
        }
    }


    return ret;






}

}

#endif // PYTHONHEPERS_H
