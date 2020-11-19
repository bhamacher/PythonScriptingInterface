#include "pythonguard.h"

using namespace zPyInt;

PythonGuard::PythonGuard()
{
    m_gstate = PyGILState_Ensure();
}

PythonGuard::~PythonGuard()
{
    PyGILState_Release(m_gstate);
}
