#include "process_runner.h"
#include <iostream>

int main()
{
#ifdef _WIN32
    auto handle = run_process("cmd", {"/C", "echo Hello from child"});
#else
    auto handle = run_process("echo", {"Hello from child"});
#endif

    int code = wait_process(handle);

    std::cout << "Child exit code: " << code << std::endl;

    return 0;
}
