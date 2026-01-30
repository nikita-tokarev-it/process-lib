#include "process_runner.h"

#ifdef _WIN32

#include <windows.h>
#include <sstream>

ProcessHandle run_process(const std::string& program,
                          const std::vector<std::string>& args)
{
    std::stringstream cmd;
    cmd << program;

    for (auto& arg : args)
        cmd << " " << arg;

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    CreateProcessA(
        NULL,
        cmd.str().data(),
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );

    return pi;
}

int wait_process(ProcessHandle handle)
{
    WaitForSingleObject(handle.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(handle.hProcess, &exitCode);

    CloseHandle(handle.hProcess);
    CloseHandle(handle.hThread);

    return (int)exitCode;
}

#else

#include <unistd.h>
#include <sys/wait.h>

ProcessHandle run_process(const std::string& program,
                          const std::vector<std::string>& args)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(program.c_str()));

        for (auto& a : args)
            argv.push_back(const_cast<char*>(a.c_str()));

        argv.push_back(nullptr);

        execvp(program.c_str(), argv.data());
        exit(1);
    }

    return pid;
}

int wait_process(ProcessHandle pid)
{
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    return -1;
}

#endif
