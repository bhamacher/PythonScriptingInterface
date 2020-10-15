#ifndef PYTHONDICTONARY_H
#define PYTHONDICTONARY_H

#include <QObject>
#include "pyhelper.h"
#include <QMap>
namespace zPyInt {
class PythonBinding;
}

/**
 * @brief The PythonDictonary class
 *
 * Provides an abstraction Layer to use a Pythin Dictonary.
 * An Object of this class is provided by PythonBinding.
 *
 * The Object behaves like a simple map.
 * 1. You can insert objects with a key.
 * 2. Read the with the key
 * 3. remove them with the key
 *
 * If fixtype is set to true, insert or value will throw a exception,
 * if a type changed. This happens only on the C++ side not on the Python side.
 * That means as long as C++ will not access the object everything works just fine.
 * The type used at the fist C++ call is essential.
 *
 */
namespace zPyInt {
class PythonDictonary
{
public:
    explicit PythonDictonary();
    ~PythonDictonary();
    /**
     * @brief value return value to key
     * @param p_key: key for object
     * @return object or NULL if key does not exist
     */
    PyObject *value(const QString &p_key);
    /**
     * @brief insert: inserts a object with key
     * @param p_key
     * @param p_value
     * @return success/fail
     *
     * @exception std::runtime_error();
     */
    bool  insert(const QString &p_key, PyObject* p_value);
    /**
     * @brief remove: removes object from map
     * @param p_key
     *
     * @exception std::runtime_error();
     */
    void remove(const QString& p_key);
    /**
     * @brief clear removes all items in the list
     */
    void clear();
    /**
     * @brief operator =
     * Copys abstraction layer object
     */
    PythonDictonary &operator=(const PythonDictonary& dict);
    /**
     * @brief operator []
     * same as value. Will not work with [key]=object.
     * This has internal reasons.
     */
    PyObject* operator[](const QString &key); //TODO: Set values with this operator: Also I am not sure i should use some more const
    bool forceType() const;
    void setForceType(bool forceType);

private:
    /**
     * @brief CheckType checks for type changes
     * @param p_key: value identifier
     * @param p_value: value to check
     * @return good/bad
     *
     * @exception std::runtime_error();
     */
    bool CheckType(const QString &p_key,PyObject* p_value);
    QMap<QString,QString> typeMap;
    int cval;
    QString m_name;
    PyObject *m_pDict, *m_pVal;
    bool m_forceType;



    friend PythonBinding;

};
}

#endif // PYTHONDICTONARY_H
