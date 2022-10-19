#pragma once

#include <cassert>
#include <stdint.h>

#include "logging/Log.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#define LASKA_API extern "C" __declspec(dllexport)

#define LASKA_LOG_ENABLE true

#if LASKA_LOG_ENABLE
    #define LASKA_LOG_TRACE(...) ::Laska::Logger::GetLogger()->trace(__VA_ARGS__)
    #define LASKA_LOG_INFO(...) ::Laska::Logger::GetLogger()->info(__VA_ARGS__)
    #define LASKA_LOG_WARN(...) ::Laska::Logger::GetLogger()->warn(__VA_ARGS__)
    #define LASKA_LOG_ERROR(...) ::Laska::Logger::GetLogger()->error(__VA_ARGS__)
    #define LASKA_LOG_CRITICAL(...) ::Laska::Logger::GetLogger()->critical(__VA_ARGS__)
#else
    #define LASKA_LOG_TRACE(...)    
    #define LASKA_LOG_INFO(...)     
    #define LASKA_LOG_WARN(...)     
    #define LASKA_LOG_ERROR(...)    
    #define LASKA_LOG_CRITICAL(...) 
#endif 

#ifdef _DEBUG
    #define LASKA_CHECK(expression) if (!(expression)) { LASKA_LOG_CRITICAL(#expression " failed."); exit(1); } 
    #define LASKA_ASSERT(stmt) assert(stmt)
#else
    #define LASKA_CHECK(expression) expression
    #define LASKA_ASSERT(stmt) stmt
#endif
