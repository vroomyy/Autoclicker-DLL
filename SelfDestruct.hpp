#pragma once

#include <Windows.h>
#include <filesystem>
#include <string>
#include "Utils.hpp"

namespace selfdestruct {

	extern void clear_traces();
	extern void byebye(HMODULE hmod);
	
}