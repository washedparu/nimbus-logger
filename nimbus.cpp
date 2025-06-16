#include "nimbus.h"

#include <iostream>
#include <fstream>
#include <string_view>
#include <filesystem>
#include <cstdarg>
#include <cstring>

namespace nimbus {
    inline std::ofstream logFile;

    void setup_logging(const char* source_file) {
        namespace fs = std::filesystem;
        if (!fs::exists("logs")) {
            fs::create_directory("logs");
        }

        const char* base_name = std::strrchr(source_file, '/');
        if (!base_name) base_name = std::strrchr(source_file, '\\');
        base_name = base_name ? base_name + 1 : source_file;

        std::string filename(base_name);
        size_t dot = filename.find_last_of('.');
        if (dot != std::string::npos)
            filename = filename.substr(0, dot);

        std::string log_path = "logs/" + filename + ".log";
        logFile.open(log_path);
    }

    void log_message(nl_log_level level, const char* file, int line, const char* fmt, va_list args) {
        constexpr const char* logLabels[] = {
            "[DEBUG]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[CRITICAL]: ", "[FATAL]: "
        };
        constexpr const char* logColors[] = {
            "\033[92m", "\033[93m", "\033[38;5;208m", "\033[91m", "\033[95m", "\033[31m"
        };

        constexpr size_t BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];
        vsnprintf(buffer, BUFFER_SIZE, fmt, args);

        std::cout << logColors[level] << logLabels[level]
                  << "[" << file << ":" << line << "] " << buffer << "\033[0m\n";

        if (logFile.is_open()) {
            logFile << logLabels[level]
                    << "[" << file << ":" << line << "] " << buffer << "\n";
            logFile.flush();
        }
    }
}


extern "C" {

void nl_setup_logging(const char* source_file) {
    nimbus::setup_logging(source_file);
}

void nl_log(nl_log_level level, const char* file, int line, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    nimbus::log_message(level, file, line, fmt, args);
    va_end(args);
}

}
