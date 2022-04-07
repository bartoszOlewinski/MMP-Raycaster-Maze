//
// Created by Bartosz Olewinski on 28/03/2022.
//

#include <map>
#include <vector>
#include <iostream>

#include "PythonRunner.h"

bool PythonRunner::checkPyGlobals() {




    return false;
}

/*
int PythonRunner::getPyAction() {
    int action = -1;

    FILE* PGlobalVariablesFile = fopen("Actions.py", "r");

    PyObject *dict;


    Py_Initialize();


    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

    pName = PyUnicode_FromString((char*)"Agent");

    pModule = PyImport_Import(pName);

    pFunc = PyObject_GetAttrString(pModule, (char*)"run");

    pArgs = PyTuple_Pack(0);

    pValue = PyObject_CallObject(pFunc, pArgs);


    if (PGlobalVariablesFile) {
        dict = PyEval_GetGlobals();

        std::vector<int> intVector;

        PyObject *pKeys = PyDict_Keys(dict);
        PyObject *pValues = PyDict_Values(dict);




        intVector.reserve(PyDict_Size(dict));

        for (int i = 0; i < PyDict_Size(dict); ++i) {
            intVector.push_back((int) PyLong_AsLong(PyList_GetItem(pValues, i)));
            std::cout<<intVector.at(i)<<std::endl;
        }



    }




    return action;
}
 */


