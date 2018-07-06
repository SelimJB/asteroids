#ifndef SCRIPTMANAGER
#define SCRIPTMANAGER

#include <Python.h>
#include <vector>

class ScriptManager{
	private:
	PyObject *pName, *pModule, *pFunc, *pyValue, *pyResult, *pArgs;
	static bool Py_Initialized;
	public:
	ScriptManager(const char* scriptName, const char* functionName);
	int GetOuput(std::vector<float*> inputs);
};

#endif