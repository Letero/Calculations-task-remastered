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
   * @brief Read config file, default path defined in Common.h file
   * @param[out] number of threads
   * @return Error code specified in Common.h file
   * */
  errorCode_t readConfig();
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
};

#endif //FILEMANAGER_H