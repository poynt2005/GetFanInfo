#include "pythonBinding.h"
#include "../GetFanInfo.h"

#include <iostream>

static PyObject *PyGetFanInfo(PyObject *self, PyObject *args)
{

    std::vector<std::map<std::string, val>> groupInfo;
    GetFanInfo(groupInfo);

    auto getPyObj = [](const std::string &k, const val &v) -> PyObject *
    {
        PyObject *pyTempDict = PyDict_New();
        switch (v.valType)
        {
        case STRING_TYPE:
            PyDict_SetItemString(pyTempDict, k.data(), PyUnicode_FromString(v.stringVal.data()));
            break;
        case NUMBER_TYPE:
            PyDict_SetItemString(pyTempDict, k.data(), PyFloat_FromDouble(v.numberVal));
            break;
        case BOOLEAN_TYPE:
            PyDict_SetItemString(pyTempDict, k.data(), PyBool_FromLong(static_cast<long>(v.boolVal)));
            break;
        case NULL_TYPE:
            PyDict_SetItemString(pyTempDict, k.data(), Py_None);
            break;
        }
        return pyTempDict;
    };
    PyObject *pyFanInfoGroupList = PyList_New(0);

    for (int i = 0; i < groupInfo.size(); i++)
    {
        auto info = std::move(groupInfo[i]);
        std::map<std::string, val>::iterator it;

        PyObject *pyFanInfoDict = PyDict_New();

        for (it = info.begin(); it != info.end(); it++)
        {
            std::string keyName = std::move(it->first);
            val value = std::move(it->second);

            PyObject *pyTempDict = getPyObj(keyName, value);
            PyObject *pyWMITempDict = PyDict_New();
            PyObject *pyDictUpdatedResult;
            if (!keyName.rfind("__", 0))
            {
                pyDictUpdatedResult = PyObject_CallMethod(pyWMITempDict, "update", "O", pyTempDict);
            }
            else
            {
                pyDictUpdatedResult = PyObject_CallMethod(pyFanInfoDict, "update", "O", pyTempDict);
            }

            PyDict_SetItemString(pyFanInfoDict, "WMIQueryIndicators", pyWMITempDict);
            PyList_Insert(pyFanInfoGroupList, i, pyFanInfoDict);

            Py_DECREF(pyDictUpdatedResult);
            Py_DECREF(pyTempDict);
        }
    }

    return pyFanInfoGroupList;
}

static PyMethodDef methods[] = {
    {"GetFanInfo", PyGetFanInfo, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "GetFanInfo",
    NULL,
    -1,
    methods};

PyMODINIT_FUNC
PyInit_GetFanInfo(void)
{
    return PyModule_Create(&module);
}