//
// Created by Bartosz Olewinski on 28/03/2022.
//

#ifndef RAYCASTER_PYTHONRUNNER_H
#define RAYCASTER_PYTHONRUNNER_H

//define recommended by embedded Python documentation
#define PY_SSIZE_T_CLEAN

#include <Python.h>

/**
 * Class responsible for running embedded
 * Python scripts, and retrieving information from it
 */
class PythonRunner {

public:

    /**
     * Gets AI action taken from .txt file
     * @param value int to which action will be assigned to
     */
    void getPyAction(int *value);

    void setUpPyEnv();

    /**
     * Finalizes Python's embedded environment
     */
    static void closePyEnv();

    /**
     * Runs Python's script for the AI
     */
    void runPyAI();

    /**
     * Releases Python's GIL,
     * used when C++ thread is finished
     */
    void releaseLock();


private:

    PyGILState_STATE gstate;

    bool stopThread;


};




#endif //RAYCASTER_PYTHONRUNNER_H
