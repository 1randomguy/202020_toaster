#include "wintoastlib.h"
#include "Toaster.h"
#include <string>
#include <windows.h>

using namespace WinToastLib;

int main() {
    if (!WinToast::isCompatible()) {
        std::wcerr << L"Error, your system in not supported!" << std::endl;
        return -1;
    }
    Toaster t = Toaster();
    t.activate();
    return 0;
}