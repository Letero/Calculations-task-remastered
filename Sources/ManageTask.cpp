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
    LARGE_INTEGER start_fun, end_fun, frequency; // flags - start and end of function
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_fun);
    AllTasks newTask(singleTaskStructObj);
    if (NO_ERR == newTask.executeTask(singleTaskStructObj.result)) //execute every task line by line, save result to singleTask struct
    {
        singleTaskStructObj.errorFlag = true;
    }
    else
    {
        singleTaskStructObj.errorFlag = false;
    }
    QueryPerformanceCounter(&end_fun);
    singleTaskStructObj.timeMS = static_cast<double>(end_fun.QuadPart - start_fun.QuadPart) / (frequency.QuadPart / 1000.0); // in ms
    printResults();
}

void ManageTask::printResults()
{
    if (singleTaskStructObj.errorFlag == false)
    {
        std::cout << line << ": ERROR_INPUT_DATA ==> " << singleTaskStructObj.timeMS << std::endl;
    }
    else
    {
        std::cout << line << " ==>" << singleTaskStructObj.result << " ==> " << singleTaskStructObj.timeMS << std::endl;
    }
}