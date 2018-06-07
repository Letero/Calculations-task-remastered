#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Common.h"
#include <string>
#include <fstream> //file stream library
#include <sstream>
#include <iostream>

class FileManager
{
  public:
    /**
  * @brief Overloaded constructor
  */
    FileManager();
    /**
   * @brief Simple get() function
   * @return vector of singleTask structs
   * */
    std::vector<singleTask> getTasksDataVector();
    /**
   * @brief Read config file, default path defined in Common.h file
   * @param[out] number of threads
   * @return Error code specified in Common.h file
   * */
    errorCode_t readConfig();
    /**
   * @brief Simple get() function
   * @return singleTask struct object
   * */
    singleTask getSingleTaskStruct();
    /**
     * @brief Simple getter
     * @return number of additional threads 
     * */
    int getAdditionalThreadsNo();
    /**
   * @brief Deconstructor
   * */
    ~FileManager();

  private:
    /**
   * @brief Check this macro in Common.h file 
   * */
    DISABLE_UNUSED_CONSTUCTORS(FileManager);
    /**
   * @brief amount of additional threads from config.txt file
   * */
    int additionalThreads;
    /**
   * @brief Variable storing config file name
   * */
    std::string configFile;
    /**
   * @brief Variable storing object of singleTask struct
   * */
    singleTask singleTaskStructObject;
    /**
   * @brief Vector storing singleTask struct object containing data
   * */
    std::vector<singleTask> tasksDataVector;
    /**
   * @brief Helper function, extracts data from lines and saves to singleTask struct object
   * @param[in] line to operate on
   * return Void
   * */
    void saveToStruct(const std::string &line);
};

#endif //FILEMANAGER_H