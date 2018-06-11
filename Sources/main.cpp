#include "../Headers/Common.h"
#include "../Headers/FileManager.h"
#include "../Headers/ManageTask.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <mutex>
std::mutex check_mutex;
int threadsCounter = 0;
bool signalFlag = false;

void signal_handler(int signal_num)
{
    signalFlag = true;
}

void doTheTask(const std::string &line)
{
    ++threadsCounter;
    ManageTask taskToCalc(line);
    std::lock_guard<std::mutex> guard(check_mutex);
    --threadsCounter;
}

int main()
{
    signal(SIGINT, signal_handler);

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
    std::thread thr;
    bool flag;
    while (getline(std::cin, line))
    {
        flag = true;
        while (flag)
        {
            if (threadsCounter < threadNo)
            {
                thr = std::thread(&doTheTask, line);
                thr.detach();
                flag = false;
            }
        }
        if (true == signalFlag) // CTRL+C used, stop reading input
        {
            break;
        }
    }
    while (threadsCounter) // wait for all threads to finish
    {
    }

    QueryPerformanceCounter(&end);
    interval = static_cast<double>(end.QuadPart - start.QuadPart) / (frequency.QuadPart / 1000.0); // result in ms
    std::cout << "\nTotal time: " << interval << "ms" << std::endl;

    exit(0);
}