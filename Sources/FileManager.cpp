#include "../Headers/FileManager.h"

FileManager::~FileManager() {}

FileManager::FileManager() : configFile(CONFIG_FILE_PATH)
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

void FileManager::saveToStruct(const std::string &line)
{
    singleTaskStructObject.parameters.clear();
    std::stringstream stream(line);
    int iter = 0;
    int n;
    while (1)
    {
        stream >> n;
        if (!stream)
        {
            break;
        }
        if (iter == 0) //if iter == 0 it means we are at start of a line, which should be operation ID
        {
            singleTaskStructObject.taskID = static_cast<operations_t>(n);
        }
        else
        {
            singleTaskStructObject.parameters.push_back(n);
        }
        ++iter;
    }
    singleTaskStructObject.paramCount = --iter;
    this->tasksDataVector.push_back(singleTaskStructObject);
}

singleTask FileManager::getSingleTaskStruct()
{
    return singleTaskStructObject;
}

std::vector<singleTask> FileManager::getTasksDataVector()
{
    return tasksDataVector;
}
int FileManager::getAdditionalThreadsNo()
{
    return additionalThreads;
}