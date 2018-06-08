#include "../Headers/Common.h"
#include "../Headers/FileManager.h"
#include "../Headers/TaskThread.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <mutex>

void doTheTask(const std::string &line)
{
    TaskThread taskToCalc(line);
    Sleep(3000);
}

int main()
{
    LARGE_INTEGER start, end;              // flags -start and end of program
    QueryPerformanceCounter(&start);       //time measurment
    LARGE_INTEGER frequency;               //time measurment
    QueryPerformanceFrequency(&frequency); //time measurment
    double interval;                       //time measurment
    FileManager fmObject;

    if (NO_ERR != fmObject.readConfig())
    {
        std::cout << "Problem with reading config file! Program exits." << std::endl;
        return -1;
    }

    int threadNo = 1 + fmObject.getAdditionalThreadsNo(); // minimum one thread for calculations + additional from config file

    std::string line;
    std::thread thr[threadNo];
    bool hasTaskStarted;

    while (getline(std::cin, line))
    {
        hasTaskStarted = true;
        while (hasTaskStarted)
        {
            for (int i = 0; i < threadNo; ++i)
            {
                thr[i] = std::thread(&doTheTask, line);
                if (thr[i].joinable())
                {
                    thr[i].join();
                    hasTaskStarted = false;
                    break;
                }
            }
        }
    }

    QueryPerformanceCounter(&end);
    interval = static_cast<double>(end.QuadPart - start.QuadPart) / (frequency.QuadPart / 1000.0); // result in ms
    std::cout << "\nTotal time: " << interval << "ms" << std::endl;

    return 0;
}