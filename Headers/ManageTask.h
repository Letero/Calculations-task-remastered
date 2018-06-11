#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include "Common.h"
#include "AllTasks.h"
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h> //windows library, QueryPerformanceCounter used from this lib

class ManageTask
{
public:
  explicit ManageTask(const std::string &newLine);
  ~ManageTask();

private:
  /**
   * @brief Variable storing object of singleTask struct
   * */
  singleTask singleTaskStructObj;
  /**
     * @brief String with data to operate on
     * */
  std::string line;
  /**
   * @brief Helper function, extracts data from lines and saves to singleTask struct object
   * @param[in] line to operate on
   * @return Void
   * */
  void saveToStruct();
  /**
     * @brief Calculate given task and save results
     * @return Void 
     * */
  void calculateSingleTask();
  /**
   * @brief Print results after calculating task
   * */
  void printResults();
};

#endif //TASKTHREAD_H
