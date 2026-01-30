#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
typedef PROCESS_INFORMATION ProcessHandle;
#else
#include <sys/types.h>
typedef pid_t ProcessHandle;
#endif

ProcessHandle run_process(const std::string& program,
                          const std::vector<std::string>& args);

int wait_process(ProcessHandle handle);
