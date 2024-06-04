#pragma once

class Toaster
{
private:
    std::wstring appName;
    std::wstring appUserModelID;
    std::wstring text;
    std::wstring imagePath;
    std::wstring attribute;
    std::vector<std::wstring> actions;
    INT64 expiration;
public:
    Toaster(/* args */);
    int activate();
};