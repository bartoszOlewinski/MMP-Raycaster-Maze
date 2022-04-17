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


private:




};




#endif //RAYCASTER_PYTHONRUNNER_H
