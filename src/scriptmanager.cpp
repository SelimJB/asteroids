#include "scriptmanager.h"
#include "debug.h"
#include <stdexcept>
#include <string>
using namespace std;

bool ScriptManager::Py_Initialized = false;

// Tester les catch d'exceptions

ScriptManager::ScriptManager(const char* scriptName, const char* functionName){
	if (!Py_Initialized){
		Py_Initialize();
		Py_Initialized = true;
	}
	PyObject *pName = PyString_FromString(scriptName);
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != NULL){
	}
	else {
		throw runtime_error(string("aze : ") + string(scriptName));
	}


}