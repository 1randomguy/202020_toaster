// Argus is a small utility that reminds you to give your eyes a break.
// Copyright (C) 2024  Benedikt von Blomberg

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "wintoastlib.h"
#include "Toaster.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <chrono>

using namespace WinToastLib;

void clearScreen() {
    // ANSI escape code to clear the screen
    std::cout << "\033[2J\033[1;1H";
}

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
        clearScreen();
        std::cout << "Time left: " << int(seconds_until_toast / 60) << "min, " << seconds_until_toast - (int(seconds_until_toast / 60) * 60) << "sec";
        // std::cout << " ....Currently sleeping for " << sleep_ms << std::endl;
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