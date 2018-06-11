#include "../Headers/FileManager.h"

FileManager::~FileManager() {}

FileManager::FileManager() : additionalThreads(0), configFile(CONFIG_FILE_PATH)
{
}

errorCode_t FileManager::readConfig()
{
    errorCode_t retError = NO_ERR;
    bool wasFileOpenedFlag = false; //flag used to check if file opened correctly
    std::string line;
    std::ifstream newFile(configFile);
    int temp = 0; //temporary value to store amount of threads extracted from file
    if (newFile.is_open())
    {
        wasFileOpenedFlag = true;
        for (int i = 1; i <= 4; ++i)
        {
            getline(newFile, line);
        }
        std::stringstream stream(line);
        while (1)
        {
            stream >> temp;
            if (!stream)
            {
                break;
            }
        }
        newFile.close();
    }
    if (false == wasFileOpenedFlag)
    {
        retError = CONFIG_FILE_READ_ERR;
    }
    else
    {
        additionalThreads = temp;
    }
    return retError;
}

int FileManager::getAdditionalThreadsNo()
{
    return additionalThreads;
}