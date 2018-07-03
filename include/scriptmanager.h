#ifndef SCRIPTMANAGER
#define SCRIPTMANAGER

#include <Python.h>

class ScriptManager{
	private:
	PyObject *pName, *pModule, *pFunc, *pyValue, *pyResult, *pArgs;
	static bool Py_Initialized;
	public:
	ScriptManager(const char* scriptName, const char* functionName);
};

#endif