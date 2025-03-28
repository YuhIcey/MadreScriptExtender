#pragma once

// Core Windows headers
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <cstdarg>

// Useful STL & utilities
#include <thread>
#include <mutex>
#include <chrono>
#include <filesystem>
#include <functional>
#include <algorithm>
#include <cassert>

// Project-wide types
#include "Types.h"

// Game interaction stubs (define these properly later)
#include "GameAPI.h"
#include "HookUtils.h"
#include "Networking.h"
#include "GameSync.h"
#include "ChatSystem.h"
