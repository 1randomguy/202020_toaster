#include "wintoastlib.h"
#include "Toaster.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <chrono>

using namespace WinToastLib;

int main() {
    if (!WinToast::isCompatible()) 
    {
        std::wcerr << L"Error, your system in not supported!" << std::endl;
        return -1;
    }
    int reminder_interval_min = 20;
    
    int seconds_until_toast = reminder_interval_min * 60;
    int sleep_ms = 1000;
    auto timestamp = std::chrono::system_clock::now();
    while (true)
    {
        if (seconds_until_toast == 0)
        {
            seconds_until_toast = reminder_interval_min * 60;
            int response = send_toast();
            continue;
        }
        std::cout << "Time left: " << int(seconds_until_toast / 60) << "min, " << seconds_until_toast - (int(seconds_until_toast / 60) * 60) << "sec";
        std::cout << " ....Currently sleeping for " << sleep_ms << std::endl;
        Sleep(sleep_ms);
        seconds_until_toast --;
        
        if (seconds_until_toast % 16 == 0)
        {
            auto now = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = now - timestamp;
            int ms_diff = int(elapsed_seconds.count() * 1000) - 16 * 1000;
            // try to catch up
            ms_diff += ms_diff >> 1;
            sleep_ms -= ms_diff >> 4;
            timestamp = now;
        }
    }
    return 0;
}