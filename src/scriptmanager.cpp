#include "scriptmanager.h"
#include "debug.h"
#include <stdexcept>
#include <string>
using namespace std;

bool ScriptManager::Py_Initialized = false;

ScriptManager::ScriptManager(const char *scriptName, const char *functionName)
{
	if (!Py_Initialized)
	{
		Py_Initialize();
		Py_Initialized = true;
	}
	PyObject *pName = PyString_FromString(scriptName);
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, functionName);
		if (!pFunc || !PyCallable_Check(pFunc))
			throw runtime_error(string("ScriptManager error : function \"") + string(functionName) + string("\" not found"));
	}
	else
	{
		throw runtime_error(string("ScriptManager error : script \"") + string(scriptName) + string("\" is not found"));
	}
}

int ScriptManager::GetOuput(vector<float *> inputs)
{
	pArgs = PyTuple_New(inputs.size());
	for (size_t i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] != NULL)
		{
			pyValue = PyFloat_FromDouble(*inputs[i]);
			PyTuple_SetItem(pArgs, i, pyValue);
		}
		else
		{
			pyValue = Py_None;
			PyTuple_SetItem(pArgs, i, pyValue);
		}
	}
	pyResult = PyObject_CallObject(pFunc, pArgs);
	return PyInt_AsLong(pyResult);
}