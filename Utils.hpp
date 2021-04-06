#pragma once

#include <string>
#include <random>
#include <iostream>
#include <string>
#include "Global.hpp"

namespace utils {

    __forceinline int random(float min_value, float max_value) {
        std::random_device device;
        std::mt19937 rng(device());
        std::uniform_real_distribution<> dist(min_value, max_value);

        return dist(rng);
    }

    __forceinline void init_console()
    {
        AllocConsole();
        ShowWindow(GetConsoleWindow(), SW_SHOW);

        FILE* fIn;
        FILE* fOut;

        freopen_s(&fIn, "conin$", "r", stdin);
        freopen_s(&fOut, "conout$", "w", stdout);
    }

    __forceinline void destroy_console()
    {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        FreeConsole();
    }


    __forceinline void ask_config()
    {
        std::string input;
        printf("Clicks Per Second [L]\n");
        std::getline(std::cin, input);


        config::left_cps = std::stoi(input);
        global::initialized = true;

    }

}