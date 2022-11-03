//
// Created by Bartosz Olewinski on 28/03/2022.
//


#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>


#include "PythonRunner.h"


void PythonRunner::getPyAction(int *value) {
    int action;

/*
    std::ifstream logFile("pythonLog.txt");
    std::string logString;
    while (std::getline(logFile, logString)) {
        std::cout <<logString<< std::endl;
    }
    */

    std::ifstream ActionFile("actionToTake.txt");
    std::string fileText;
    const char* result;

    std::getline(ActionFile, fileText);

    result = &fileText[0];
    //std::cout<<"PYTHON's decision: "<<result<<std::endl;


    //converting string result from python into int
    //NO ACTION TAKEN
    if (strcmp(result, "-1") == 0) {
        action = -1;

        //GO FORWARD
    } else if (strcmp(result, "1") == 0) {
        action = 1;

        //GO BACKWARDS
    } else if (strcmp(result, "2") == 0) {
        action = 2;

        //TURN LEFT
    } else if (strcmp(result, "3") == 0) {
        action = 3;

        //TURN RIGHT
    } else if (strcmp(result, "4") == 0) {
        action = 4;

        //USE KEY
    } else if (strcmp(result, "5") == 0) {
        action = 5;

        //RESET MAP
    } else if (strcmp(result, "-99") == 0) {
        action = -99;

    }
    //if missing input then NO ACTION -1
    else {
        action = -1;
    }

    *value = action;

    ActionFile.close();
}

void PythonRunner::runPyAI() {

    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

    pName = PyUnicode_FromString((char*)"Test");

    pModule = PyImport_Import(pName);

    pFunc = PyObject_GetAttrString(pModule, (char*)"run");

    PyObject_CallObject(pFunc, nullptr);

}


void PythonRunner::setUpPyEnv() {

    //needs to be set to python directory for compiler to find Python.h file
    Py_SetPythonHome(L"C:\\Users\\barto\\AppData\\Local\\Programs\\Python\\Python310-32");


    Py_Initialize();

    //for multi-threaded support
    gstate = PyGILState_Ensure();
}

void PythonRunner::closePyEnv() {
    Py_Finalize();

}

void PythonRunner::releaseLock() {
    PyGILState_Release(gstate);
}







