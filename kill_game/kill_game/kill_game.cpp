#include "framework.h"
#include "kill_game.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <tlhelp32.h>
#include <comdef.h>

using namespace std;

//process_name must incude ".exe"
bool isProcessRunning(string process_name);
//process_name must incude ".exe"
int killProcess(string process_name);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    unsigned long TIME_FOR_GAMING = 600000;
    unsigned long TIME_FOR_WAIT = 60000;
    // process name to stop
    string PROCESS_NAME = "hl.exe";

    while (!isProcessRunning(PROCESS_NAME))
    {
        Sleep(TIME_FOR_WAIT);
    }

    Sleep(TIME_FOR_GAMING);

    while (true)
    {
        if (isProcessRunning(PROCESS_NAME))
        {
            killProcess(PROCESS_NAME);
        }
        Sleep(TIME_FOR_WAIT);
    }

    return 0;

    return 0;
}

int killProcess(string process_name)
{
    string begin_comand = "taskkill /im ";
    string comand = begin_comand + process_name;

    system(comand.c_str());

    return 0;
}

bool isProcessRunning(string process_name)
{
    const char* c_process_name = process_name.c_str();

    bool processIsRunning = false;

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            _bstr_t b(entry.szExeFile);
            const char* c = b;

            if (_stricmp(c, c_process_name) == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                processIsRunning = true;

                CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);

    return processIsRunning;
}
