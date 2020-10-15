#ifndef PYSHAREDREFERENCE_H
#define PYSHAREDREFERENCE_H
#include "pyhelper.h"

/**
 * @brief The PySharedRef class handles PyOject references
 *
 * If someone wants to use PyObject* Py_INCREF(<obj>) must be called.
 * Not doing this can have unpredictable effects. dleting an object happens
 * calling Py_DECREF(<obj>). When no reference is left the garbage collector will
 * delete the object.
 *
 * PySharedRef handles this for you. If you copy the object Py_INCREF is called.
 * Deleting the opbject or Dropping it calls Py_DECREF.
 *
 * To use it with Python functions use ref->data();
 *
 * @warning never do PyObject* obj = <PySharedRef>.data()
 *
 * It is not possible to stop this from working, but it is not safe and destroys
 * the concept
 *
 */

namespace zPyInt {
class PySharedRef
{
public:
    PySharedRef();
    /**
     * @brief PySharedRef Konstrukt object with PyObject
     * @param p_pObj: PyObject*
     *
     * example:
     * @code
     * Pythonbinding py;
     * ...
     * PySharedRef ref = py.callFunction("<function>");
     * @endcode
     */
    PySharedRef(PyObject* p_pObj);
    /**
     * @brief PySharedRef copy constructor
     * @param p_pObj
     */
    PySharedRef(const PySharedRef &p_pObj);
    ~PySharedRef();
    /**
     * @brief data returns the actual PyObject*
     * @return PyObject*
     */
    PyObject* data() const;
    /**
     * @brief operator = set reference
     * @param p_pObj: the actual PyObject*
     * @return PySharedRef
     */
    PySharedRef operator=(PyObject* p_pObj);
    /**
     * @brief operator = copy the reference
     * @param p_pObj: the ref object
     * @return PySharedRef
     *
     * @code
     * Pythonbinding py;
     * ...
     * PySharedRef ref = py.callFunction("<function>");
     * PySharedRef ref2 = ref;
     * @endcode
     */
    PySharedRef &operator=(const PySharedRef &p_pObj);

    /**
     * @brief object
     * same as data()
     */
    PyObject *object() const;
    /**
     * @brief setObject
     * Better not use.
     */
    void setObject(PyObject *object);

private:
    PyObject* m_object;
};
}

#endif // PYSHAREDREFERENCE_H
