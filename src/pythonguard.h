#ifndef PYTHONGUARD_H
#define PYTHONGUARD_H


#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")
namespace zPyInt {
class PythonGuard
{
public:
    PythonGuard();
    ~PythonGuard();
    void* operator new(std::size_t size) = delete ;
private:
    PyGILState_STATE m_gstate;
};
}
#endif // PYTHONGUARD_H
