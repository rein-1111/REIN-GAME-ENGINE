#pragma once

#include <iostream>

#ifdef DEBUG_OPENGLBACKEND

#define DEBUG_LOG_OPENGLBACKEND(x) std::cout << "[DEBUG] " << x << std::endl;
#define SUCCESS_LOG_OPENGLBACKEND(x) std::cout << "[SUCCESS] " << x << std::endl;
#define WARNING_LOG_OPENGLBACKEND(x) std::cout << "[WARNING]" << x << std::endl;
#define ERROR_LOG_OPENGLBACKEND(x) std::cout << "[ERROR] " << x << std::endl;

#else
#define DEBUG_LOG_OPENGLBACKEND(x)
#define SUCCESS_LOG_OPENGLBACKEND(x)
#define WARNING_LOG_OPENGLBACKEND(x)
#define ERROR_LOG_OPENGLBACKEND(x)
#endif