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
            singleTaskStructObject.taskID = static_cast<operations_t>(n);
        }
        else
        {
            singleTaskStructObject.parameters.push_back(n);
        }
        ++iter;
    }
    singleTaskStructObject.paramCount = --iter;
    calculateSingleTask();
}

void ManageTask::calculateSingleTask()
{
    LARGE_INTEGER start_fun, end_fun, frequency; // flags - start and end of function
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_fun);
    AllTasks newTask(singleTaskStructObject);
    if (NO_ERR == newTask.executeTask(singleTaskStructObject.result)) //execute every task line by line, save result to singleTask struct
    {
        singleTaskStructObject.errorFlag = true;
    }
    else
    {
        singleTaskStructObject.errorFlag = false;
    }
    QueryPerformanceCounter(&end_fun);
    singleTaskStructObject.timeMS = static_cast<double>(end_fun.QuadPart - start_fun.QuadPart) / (frequency.QuadPart / 1000.0); // in ms
    printResults();
}

void ManageTask::printResults()
{
    if (singleTaskStructObject.errorFlag == false)
    {
        std::cout << line << ": ERROR_INPUT_DATA ==> " << singleTaskStructObject.timeMS << std::endl;
    }
    else
    {
        std::cout << line << " ==>" << singleTaskStructObject.result << " ==> " << singleTaskStructObject.timeMS << std::endl;
    }
}