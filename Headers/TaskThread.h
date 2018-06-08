#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include "Common.h"
#include "AllTasks.h"
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h> //windows library, QueryPerformanceCounter used from this lib

class TaskThread
{
  public:
    explicit TaskThread(const std::string &newLine);
    ~TaskThread();
    void init();
    void printResults();

    //private:
    /**
   * @brief Variable storing object of singleTask struct
   * */
    singleTask singleTaskStructObject;
    /**
     * @brief String with data to operate on
     * */
    std::string line;
    /**
   * @brief Helper function, extracts data from lines and saves to singleTask struct object
   * @param[in] line to operate on
   * return Void
   * */
    void saveToStruct();
    /**
     * @brief 
     * */
    void calculateSingleTask();
};

#endif //TASKTHREAD_H
