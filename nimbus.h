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

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NL_DEBUG_LOG,
    NL_INFO_LOG,
    NL_WARN_LOG,
    NL_ERROR_LOG,
    NL_CRITICAL_LOG,
    NL_FATAL_LOG
} nl_log_level;

void nl_setup_logging(const char* source_file);
void nl_log(nl_log_level level, const char* file, int line, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#define NL_LOG(level, fmt, ...) nl_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
