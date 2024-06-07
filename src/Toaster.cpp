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

using namespace WinToastLib;

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const {
        std::wcout << L"The user clicked in this toast" << std::endl;
    }

    void toastActivated(int actionIndex) const {
        std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
    }

    void toastDismissed(WinToastDismissalReason state) const {
        switch (state) {
            case UserCanceled:
                std::wcout << L"The user dismissed this toast" << std::endl;
                break;
            case TimedOut:
                std::wcout << L"The toast has timed out" << std::endl;
                break;
            case ApplicationHidden:
                std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
                break;
            default:
                std::wcout << L"Toast not activated" << std::endl;
                break;
        }
    }

    void toastFailed() const {
        std::wcout << L"Error showing current toast" << std::endl;
        exit(5);
    }
};


int send_toast()
{
    const auto aumi = WinToast::configureAUMI(L"benedikt", L"argus", L"", L"100");
    WinToast::instance()->setAppName(L"Argus");
    WinToast::instance()->setAppUserModelId(aumi);	

    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
        return -1;
    }

    WinToastTemplate templ(WinToastTemplate::Text02);
    templ.setTextField(L"Look at a point 20 meters away for 20 seconds to relax your eyes.", WinToastTemplate::FirstLine);
    templ.setAudioOption(WinToastTemplate::AudioOption::Default);
    templ.setAttributionText(L"Reminder");

    templ.addAction(L"Dismiss");

    INT64 expiration = 2000;
    if (expiration) {
        templ.setExpiration(expiration);
    }

    if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
        std::wcerr << L"Could not launch your toast notification!";
        return -2;
    }

    // Give the handler a chance for 15 seconds (or the expiration plus 1 second)
    // Sleep(expiration ? (DWORD) expiration + 1000 : 15000);
    return 0;
}
