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


void PythonRunner::getPyAction(int *value) {
    int action = -1;

    FILE* PGlobalVariablesFile = fopen("Actions.py", "r");

    PyObject *dict;


    //NEED TO SET '2PYTHONHOME' VARIABLE MANUALLY BECAUSE CLION SETS THEM TO SOME DIRECTORY INSIDE MINGW
    Py_SetPythonHome(L"C:\\Users\\barto\\AppData\\Local\\Programs\\Python\\Python310-32");



    Py_Initialize();


    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

    pName = PyUnicode_FromString((char*)"Test");

    pModule = PyImport_Import(pName);

    pFunc = PyObject_GetAttrString(pModule, (char*)"run");

    pArgs = PyTuple_Pack(0);

    PyObject_CallObject(pFunc, pArgs);



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


    Py_Finalize();

    *value = action;

    //return action;
}



