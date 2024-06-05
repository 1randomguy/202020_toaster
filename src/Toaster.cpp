#include "wintoastlib.h"
#include "Toaster.h"
#include <string>
#include <windows.h>

using namespace WinToastLib;

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const {
        std::wcout << L"The user clicked in this toast" << std::endl;
        exit(0);
    }

    void toastActivated(int actionIndex) const {
        std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
        exit(16 + actionIndex);
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
    const auto aumi = WinToast::configureAUMI(L"benedikt", L"202020", L"", L"20161006");
    WinToast::instance()->setAppName(L"ZwanzigToaster");
    WinToast::instance()->setAppUserModelId(aumi);	

    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
        return -1;
    }

    WinToastTemplate templ(WinToastTemplate::Text02);
    templ.setTextField(L"Look at a point 20 meters away for 20 seconds to relax your eyes.", WinToastTemplate::FirstLine);
    templ.setAudioOption(WinToastTemplate::AudioOption::Default);
    templ.setAttributionText(L"Reminder");

    INT64 expiration = 200;
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
