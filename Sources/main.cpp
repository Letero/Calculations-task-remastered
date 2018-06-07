#include "../Headers/Common.h"
#include "../Headers/FileManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <mutex>

using namespace std;

void fun(const string &line)
{
    cout << "PRINT FROM THREAD WITH ID: " << this_thread::get_id()
         << "LINE = " << line << endl;
    Sleep(2000);
}

int main()
{
    FileManager test;
    if (NO_ERR != test.readConfig())
    {
        cout << "Problem with reading config file! Program exits." << endl;
        return -1;
    }
    int threadNo = 1 + test.getAdditionalThreadsNo(); // minimum one thread for calculations + additional from config file

    string line;
    thread thr[threadNo];
    bool hasTaskStarted;

    while (getline(cin, line))
    {
        hasTaskStarted = true;
        while (hasTaskStarted)
        {
            for (int i = 0; i < threadNo; ++i)
            {
                thr[i] = thread(&fun, line);
                if (thr[i].joinable())
                {
                    thr[i].join();
                    hasTaskStarted = false;
                    break;
                }
            }
        }
    }
    exit(0);
    return 0;
}