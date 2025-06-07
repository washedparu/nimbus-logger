/*
MIT License

Copyright (c) 2025 washedparu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string_view>
#include <array>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <chrono>
#include <ctime>

#define NL_NULL 0
#define NL_NULLP nullptr

#define NL_VOID                 void
#define NL_VOIDP                NL_VOID*

#define NL_STRING_VIEW          std::string_view

#define NL_INT8                 signed char
#define NL_INT16                short
#define NL_INT32                int
#define NL_INT64                long long

#define NL_UINT8                unsigned char
#define NL_UINT16               unsigned short
#define NL_UINT32               unsigned int
#define NL_UINT64               unsigned long long

#if defined(_WIN32) || defined(_WIN64)
#define NL_OS_WINDOWS
#include <windows.h>
#elif defined(__linux__)
#define NL_OS_LINUX
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace nimbus {

    enum logLevels : uint8_t {
        NL_DEBUG_LOG,
        NL_INFO_LOG,
        NL_WARN_LOG,
        NL_ERROR_LOG,
        NL_CRITICAL_LOG,
        NL_FATAL_LOG
    };

    constexpr std::array<NL_STRING_VIEW, 6> logLabels = {
        "[DEBUG]: ",
        "[INFO]: ",
        "[WARN]: ",
        "[ERROR]: ",
        "[CRITICAL]: ",
        "[FATAL]: "
    };

    constexpr std::array<const char*, 6> logColors = {
        "\033[92m",
        "\033[93m",
        "\033[38;5;208m",
        "\033[91m",
        "\033[95m",
        "\033[31m"
    };

    


    inline std::ofstream logFile;

    inline const char* filename_only(const char* path) {
        const char* file = NL_NULLP;
    #if defined(NL_OS_WINDOWS)
        file = std::strrchr(path, '\\');
    #elif defined(NL_OS_LINUX)
        file = std::strrchr(path, '/');
    #endif
        return file ? file + 1 : path;
    }
    
 
char* truncate_char(const char* input, char stopChar) {
    if (!input) return nullptr;

    const char* pos = strchr(input, stopChar);
    size_t length = pos ? (pos - input) : strlen(input);


    char* output = new char[length + 1];
    strncpy(output, input, length);
    output[length] = '\0';

    return output; 
}


    inline void setup_logging(const char* source_file = __FILE__) {
        namespace fs = std::filesystem;
        if (!fs::exists("logs")) {
            fs::create_directory("logs");
        }
        const char* base_filename = truncate_char(filename_only(source_file), '.');
        std::string log_filename = std::string("logs/") + base_filename + ".log";
        logFile.open(log_filename);
    	delete[] base_filename;
    }

    inline void log_message(logLevels level, const char* file, int line, const char* fmt, va_list args) {
        constexpr size_t BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];
        vsnprintf(buffer, BUFFER_SIZE, fmt, args);

        std::cout << logColors[level] << logLabels[level] << "[" << file << ":" << line << "] " << buffer << "\033[0m\n";

        if (logFile.is_open()) {
            logFile << logLabels[level];
            logFile << "[" << file << ":" << line << "] " << buffer << "\n";
            logFile.flush();
        }
    }

    inline void debug(const char* file, int line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        log_message(NL_DEBUG_LOG, file, line, fmt, args);
        va_end(args);
    }
    inline void info(const char* file, int line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        log_message(NL_INFO_LOG, file, line, fmt, args);
        va_end(args);
    }
    inline void warn(const char* file, int line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        log_message(NL_WARN_LOG, file, line, fmt, args);
        va_end(args);
    }
    inline void error(const char* file, int line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        log_message(NL_ERROR_LOG, file, line, fmt, args);
        va_end(args);
    }
    inline void critical(const char* file, int line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        log_message(NL_CRITICAL_LOG, file, line, fmt, args);
        va_end(args);
    }
    inline void fatal(const char* file, int line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        log_message(NL_FATAL_LOG, file, line, fmt, args);
        va_end(args);
    }
}

#define NL_FILE (nimbus::filename_only(__FILE__))
#define NL_DEBUG(fmt, ...) nimbus::debug(NL_FILE, __LINE__, fmt, ##__VA_ARGS__)
#define NL_INFO(fmt, ...) nimbus::info(NL_FILE, __LINE__, fmt, ##__VA_ARGS__)
#define NL_WARN(fmt, ...) nimbus::warn(NL_FILE, __LINE__, fmt, ##__VA_ARGS__)
#define NL_ERROR(fmt, ...) nimbus::error(NL_FILE, __LINE__, fmt, ##__VA_ARGS__)
#define NL_CRITICAL(fmt, ...) nimbus::critical(NL_FILE, __LINE__, fmt, ##__VA_ARGS__)
#define NL_FATAL(fmt, ...) nimbus::fatal(NL_FILE, __LINE__, fmt, ##__VA_ARGS__)

