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
                exit(1);
                break;
            case TimedOut:
                std::wcout << L"The toast has timed out" << std::endl;
                exit(2);
                break;
            case ApplicationHidden:
                std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
                exit(3);
                break;
            default:
                std::wcout << L"Toast not activated" << std::endl;
                exit(4);
                break;
        }
    }

    void toastFailed() const {
        std::wcout << L"Error showing current toast" << std::endl;
        exit(5);
    }
};

Toaster::Toaster(/* args */)
{
    std::wstring appUserModelID = L"";
    std::wstring text           = L"HIIII";
    std::wstring imagePath      = L"";
    std::wstring attribute      = L"default";
    std::vector<std::wstring> actions;
    INT64 expiration = 20000;
    printf("Toaster created!");
}

int Toaster::activate()
{
    WinToastTemplate::AudioOption audioOption = WinToastTemplate::AudioOption::Default;

    WinToast::instance()->setAppName(L"ZwanzigToaster");
    const auto aumi = WinToast::configureAUMI(L"benedikt", L"202020", L"", L"20161006");
    WinToast::instance()->setAppUserModelId(aumi);	

    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
        return -1;
    }

    WinToastTemplate templ(WinToastTemplate::Text02);
    templ.setTextField(text, WinToastTemplate::FirstLine);
    templ.setAudioOption(audioOption);
    templ.setAttributionText(attribute);

    for (auto const& action : actions) {
        templ.addAction(action);
    }

    if (expiration) {
        templ.setExpiration(expiration);
    }

    if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
        std::wcerr << L"Could not launch your toast notification!";
        return -2;
    }

    // Give the handler a chance for 15 seconds (or the expiration plus 1 second)
    Sleep(expiration ? (DWORD) expiration + 1000 : 15000);
    exit(2);
}
