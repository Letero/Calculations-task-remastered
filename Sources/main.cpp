#include "../Headers/Common.h"
#include "../Headers/FileManager.h"
#include "../Headers/TaskThread.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <future>
#include <chrono>

std::promise<bool> p;

void doTheTask(const std::string &line)
{
    TaskThread taskToCalc(line);
    p.set_value(true);
}

int main()
{
    using namespace std::literals::chrono_literals;
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
    auto future = p.get_future();
    auto status = future.wait_for(0ms);

    while (getline(std::cin, line))
    {
        hasTaskStarted = true;
        while (hasTaskStarted)
        {
            for (int i = 0; i < threadNo; ++i)
            {
                thr[i] = std::thread(&doTheTask, line);
                if (status == std::future_status::ready)
                {
                    std::cout << "Thread finished" << std::endl;
                    if (thr[i].joinable())
                    {
                        thr[i].join();
                        thr[i] = NULL;
                        hasTaskStarted = false;
                        break;
                    }
                }
                else
                {
                    std::cout << "Thread still running" << std::endl;
                }
            }
        }
    }

    QueryPerformanceCounter(&end);
    interval = static_cast<double>(end.QuadPart - start.QuadPart) / (frequency.QuadPart / 1000.0); // result in ms
    std::cout << "\nTotal time: " << interval << "ms" << std::endl;

    return 0;
}