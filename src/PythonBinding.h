
#ifndef __PythonBinding_h__
#define __PythonBinding_h__

// #include "DataOutputLayer.h"
// #include "DataInputLayer.h"
#include <QObject>
#include <QString>
#include <QVariant>
#include <QList>
#include <QDir>
#include "pyhelper.h"
#include "pythonobject.h"
#include "pythondictonary.h"



/**
 * @brief Top Class For Python scripting engine
 *
 * 1. Add functions to expose to Python with AddFunction();
 * 2. Create an Object with PythenBinding obj
 * 3. Load a module with obj.init(<modulename>)
 * 4. Call Functions or create Dictonaries
 *
 * This class in only useable in combination with Python.h:
 * That is because Pathon uses var types and PyObject* implments this
 * in C. Therefore you will need the Pyhton.h parsing functions.
 *
 * example:
 * @code
 *
 * static PyObject* someFunction(PyObject* self, PyObject* args){
 *          //your code here
 * }
 * void main(){
 *     PythonBinding py;
 *     PythonBinding::AddFunction("cFunction", someFunction);
 *     py.init(<your module>);
 *     py.callFunction("pythonFunction",{<Args>}); //eg. {PyLong_FromLong(3), PyLong_FromLong(5)}
 *     PythonObject obj = py.createObject("pythonClass");
 *     PythonDictonary dobj=py.createDictonary("pDict");
 * }
 * @endcode
 * Python code:
 * @code
 *    import CPPFUNC
 *    ...
 *    class pythonClass:
 *          def meth1:
 *          def meth2:
 *    ...
 *    def pythonFunction(<args>):
 *          # your code
 *
 *    def CFuncCaller:
 *          CPPFUNC.cFunction(<args>)
 *
 *    def dictUser:
 *          print(pDict)
 *
 * @endcode
 */

namespace zPyInt {
class PythonBinding : public QObject
{
    Q_OBJECT
public:
    PythonBinding();
    ~PythonBinding();
    /**
     * @brief init loads a python module
     * @param p_module: Name of the module
     * @param p_path: Path to the module folder (optional)
     */
    bool init(QString p_module, QString p_path="");
    /**
     * @brief callFunction
     * @param p_name: name of the function to call
     * @param p_args: funcrion arguments stored in a list
     * @return The function return. This is not typesafe
     *
     * @code
     * obj->callFunction("method2",{PyLong_FromLong(10), PyLong_FromLong(20)})
     * @endcode
     */
    PyObject* callFunction(QString p_name, QList<PyObject*> p_args = {}) ;
    /**
     * @brief createObject Create an instance of class p_name defined in Python.h
     * @param p_name: name of the pyhton class
     * @return An Abstraction layer to use the object
     */
    PythonObject createObject(const QString &p_name);
    /**
     * @brief createDictonary Creates a Python Dictonary useable from Python and C++
     * @param p_name: Name of the dictonary
     * @return An Abstraction layer to use the dictonary
     */
    PythonDictonary createDictonary(const QString &p_name);
    /**
     * @brief AddFunction to Python scope
     * @param name: Function name in Python
     * @return success/fail
     *
     * Call this function before you create a Pythonbinding object.
     * Calling it after init will not have any effect.
     */
    static bool AddFunction(const char* name,PyObject* (*func)(PyObject *,PyObject *));
    /**
     * @brief PyInit_emb Do not use. Never!
     * @return you should not care.
     *
     * This is based on function pointer of the type (*func)(PyObject *,PyObject *).
     * Your function must fit this type. Your function must be static as well. If you wish to
     * connect to a non static function you will need a static wrapper function.
     *
     * @code
     * class wrapperexmple{
     *  PyObject* function(PyObject * self,PyObject * args);
     *  static PyObject* function(PyObject * self,PyObject * args){
     *
     *  }
     * }
     * @endcode
     *
     */
    static PyObject* PyInit_emb(void);
    /**
     * @brief pModule Returns pointer to the python module
     * @return Python module
     *
     * Be aware what you do. Nothing is save from here.
     */
    PyObject *pModule() const;
    /**
     * @brief setPModule sets the Pythonmodule
     * @param pModule: the PythonModule
     *
     * Use is not recommended: Better Create module with \link PythonBinding::init(p_module,p_path) \endlink
     */
    void setPModule(PyObject *pModule);

private:
    static int m_objCounter;
private:
    PyObject *m_pName, *m_pModule, *m_pFunc, *m_pArgs, *m_pValue;
private:
    static bool m_initialized;
    /**
     * @brief CPPFUNCMethods: Stores to python exposed c++ methods.
     */
    static QVector<PyMethodDef> CPPFUNCMethods;
    static PyModuleDef CPPFUNCModule;
};
}
#endif
