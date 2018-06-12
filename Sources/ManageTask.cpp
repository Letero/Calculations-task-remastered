#include "../Headers/ManageTask.h"

ManageTask::~ManageTask() {}
ManageTask::ManageTask(const std::string &newLine) : line(newLine)
{
    saveToStruct();
}

void ManageTask::saveToStruct()
{
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
            singleTaskStructObj.taskID = static_cast<operations_t>(n);
        }
        else
        {
            singleTaskStructObj.parameters.push_back(n);
        }
        ++iter;
    }
    singleTaskStructObj.paramCount = --iter;
    calculateSingleTask();
}

void ManageTask::calculateSingleTask()
{
    LARGE_INTEGER start_fun, end_fun, frequency; //flags - start and end of function
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_fun);
    AllTasks newTask(singleTaskStructObj);

    singleTaskStructObj.errorFlag = newTask.executeTask(singleTaskStructObj.result);

    QueryPerformanceCounter(&end_fun);
    singleTaskStructObj.timeMS = static_cast<double>(end_fun.QuadPart - start_fun.QuadPart) / (frequency.QuadPart / 1000.0); //in ms
}

void ManageTask::printResults()
{
    if (NO_ERR != singleTaskStructObj.errorFlag)
    {
        std::cout << line << "==>" << printErrorHelper(singleTaskStructObj.errorFlag) << "==>" << singleTaskStructObj.timeMS << std::endl;
    }
    else
    {
        std::cout << line << "==>" << singleTaskStructObj.result << "==>" << singleTaskStructObj.timeMS << std::endl;
    }
}

std::string ManageTask::printErrorHelper(errorCode_t errCode)
{
    std::string errorMSG;
    switch (errCode)
    {
    case NO_ERR:
        break;
    case INVALID_PARAM:
        errorMSG = "Error! Invalid Parameter(s)!";
        break;
    case INVALID_TASK_ID:
        errorMSG = "Error! Invalid Task ID!";
        break;
    case WRONG_AMOUNT_PARAM:
        errorMSG = "Error! Wrong amount of parameters!";
        break;
    case FILE_READ_ERR:
        break;
    case FILE_SAVE_ERR:
        break;
    case CONFIG_FILE_READ_ERR:
        break;
    }
    return errorMSG;
}