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

void doTheTask(const std::string &line)
{
    ++threadsCounter; //amount of threads working
    ManageTask taskToCalc(line);
    std::lock_guard<std::mutex> guard(check_mutex);
    taskToCalc.printResults();
    --threadsCounter; //once thread is done, decrease counter so another can start
}

int main()
{
    LARGE_INTEGER start, end;              //flags - start and end of program
    QueryPerformanceCounter(&start);       //time measurment
    LARGE_INTEGER frequency;               //time measurment
    QueryPerformanceFrequency(&frequency); //time measurment
    double interval;                       //time measurment
    FileManager fmObject(CONFIG_FILE_PATH);

    if (NO_ERR != fmObject.readConfig())
    {
        std::cout << "Problem with reading config file! Program exits." << std::endl;
        return -1;
    }

    int threadNo = 1 + fmObject.getAdditionalThreadsNo(); //minimum one thread for calculations + additional from config file

    std::string line;
    std::thread thr;
    std::cout << "Press 'q' and then 'Enter' to stop user input" << std::endl;
    while (getline(std::cin, line))
    {
        bool flag = true;
        do // loop until thread is free to take the job
        {
            std::lock_guard<std::mutex> guard(check_mutex);
            if (threadsCounter < threadNo) //thread no is max number of threads running at once. If there is less running threads than this number -
            //start another, otherwise wait until one of them finishes its job
            {
                thr = std::thread(&doTheTask, line); //start thread
                thr.detach();                        //detach thread so it will work independly of main thread
                flag = false;                        //thread started so stop waiting for free one, break loop
            }
        } while (flag);

        if (line == "q")
        {
            break;
        }
    }
    while (threadsCounter) //wait for all threads to finish
    {
    }
    Sleep(1); // sleep for 1 ms to make sure everything will be printed. Without it some prints could be ommited

    QueryPerformanceCounter(&end);
    interval = static_cast<double>(end.QuadPart - start.QuadPart) / (frequency.QuadPart / 1000.0); //result in ms
    std::cout << "\nTotal time: " << interval << "ms" << std::endl;

    return 0;
}