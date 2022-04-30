//
// Created by Bartosz Olewinski on 28/03/2022.
//

#ifndef RAYCASTER_PYTHONRUNNER_H
#define RAYCASTER_PYTHONRUNNER_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>

class PythonRunner {

public:
    bool checkPyGlobals();

    void getPyAction(int *value);

    void setUpPyEnv();

    void closePyEnv();

    void runPyAI();

    void releaseLock();


private:

    PyGILState_STATE gstate;

    bool stopThread;


};




#endif //RAYCASTER_PYTHONRUNNER_H
