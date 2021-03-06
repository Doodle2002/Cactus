#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional> 

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Cactus/Core/Log.h"
#include "Cactus/Debug/Instrumentor.h"

#ifdef CACTUS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif