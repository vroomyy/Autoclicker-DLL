#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <filesystem>

#include "Global.hpp"
#include "Utils.hpp"
#include "SelfDestruct.hpp"


void main(HMODULE hmodule)
{
    SetConsoleTitleA("not vroom!#1337");
    system("CLS");
    std::cout << "Clicker made by vroom" << std::endl;
    std::cout << "Press [DEL] to selfdestruct..." << std::endl;

    do
    {
        HWND minecraft = FindWindowA("LWJGL", NULL);

        if (GetAsyncKeyState(VK_DELETE))
            global::selfdestruct = true;

        if (GetForegroundWindow() == minecraft) {

            if (GetAsyncKeyState(VK_LBUTTON))
            {
                SendMessageA(minecraft, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
                SendMessageA(minecraft, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(0, 0));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(utils::random(955, 1055) / config::left_cps));
    } while (!global::selfdestruct);

    selfdestruct::clear_traces();
    selfdestruct::byebye(hmodule);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        utils::init_console();
        utils::ask_config();

        while(!global::initialized){}

        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr));
    }

    return TRUE;
}

