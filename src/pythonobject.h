#ifndef PYTHONOBJECT_H
#define PYTHONOBJECT_H

#include <QObject>
#include "pyhelper.h"
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")
namespace zPyInt {
class PythonBinding;
}
namespace zPyInt {
/**
 * @brief The PythonObject class
 *
 * Provides an Abstractionlayer for Python Objects
 *
 * You can call functions once created the object.
 *
 */
class PythonObject
{
public:
    explicit PythonObject();
    ~PythonObject();
    /**
     * @brief callFunction Call a Python function
     * @param p_name: name of the function
     * @return return of the function. This is not typesafe.
     */
    PyObject* callFunction(const QString &p_name, QList<PyObject*> p_args = {});
    /**
     * @brief getAttribute get an instance attribute
     * @param p_name: name of the attribute
     * @return Value of the attribute. This is not typesafe.
     *
     * This is an instance attribute not an class attribute:
     *
     * @code
     * class example:
     *     classAttribute = <val>               //it is not this (is not supported)
     *     def __init__(self,instAttribute):
     *         self.instAttribute=instAttribute //it is this
     * @endcode
     */
    PyObject *getAttribute(const QString p_name);
    /**
     * @brief setAttribute set an instance Attribute
     * @param p_name: name of the Attribute
     * @param p_obj: value to set
     *
     * see also: getAttribute()
     */
    void setAttribute(const QString &p_name, PyObject* p_obj);
    PyObject *getPInst() const;
    void setPInst(PyObject *pInst);
    PythonObject &operator=(const PythonObject& obj);

private:
    PyObject *m_pClass, *m_pFunc, *m_pArgs, *m_pValue, *m_pInst;
    friend PythonBinding;
};
}
#endif // PYTHONOBJECT_H
