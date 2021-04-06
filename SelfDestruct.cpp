#define _CRT_SECURE_NO_WARNINGS
#include "SelfDestruct.hpp"

namespace selfdestruct {

	void clear_traces()
	{
        std::string path = getenv("APPDATA");
        path += "\\Microsoft\\Windows\\Recent\\";

        for (const auto& file : std::filesystem::directory_iterator(path))
        {
            std::string path = file.path().filename().string();

            if (path.find(".dll") != std::string::npos)
            {
                std::filesystem::remove(file);
            }
        }

        std::wstring m_path = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\\dll";
        HKEY hKey;
        RegOpenKeyEx(HKEY_CURRENT_USER, m_path.c_str(), 0, KEY_ALL_ACCESS, &hKey);

        DWORD dwNumValues, dwValueNameLen;
        if (RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0,
            &dwNumValues, &dwValueNameLen, 0, 0, 0) == ERROR_SUCCESS)
        {
            TCHAR* tchValName = new TCHAR[dwValueNameLen + 1];
            for (int i = dwNumValues - 1; i >= 0; --i)
            {
                DWORD dwLen = dwValueNameLen + 1;
                if (RegEnumValue(hKey, i, tchValName, &dwLen, 0, 0, 0, 0) == ERROR_SUCCESS)
                    RegDeleteValue(hKey, tchValName);
            }
            delete[] tchValName;
        }
	}

    void byebye(HMODULE hmod)
    {
        utils::destroy_console();
        FreeLibraryAndExitThread(hmod, 0);
    }
}