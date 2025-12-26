#ifndef _PROCESS_HPP
#define _PROCESS_HPP

// [INCLUDES]
#include <string>

// [NAMESPACE]
namespace Process
{
    void Setup();

    // =========================
    // [BASIC INFO]
    // =========================
    int GetPID();
    int GetParentPID();
    int GetProcessGroupID();

    // =========================
    // [FOREGROUND / BACKGROUND]
    // =========================

    // True if process is attached to a terminal
    bool HasTerminal();

    // True if running in foreground (false = background or no tty)
    bool IsForeground();

    // =========================
    // [TERMINATION]
    // =========================

    // Terminates the process immediately
    [[noreturn]] void Terminate(int exit_code = 0);

    // =========================
    // [WORKING DIRECTORY]
    // =========================

    // Get current working directory
    std::string GetWorkingPath();

    // Set current working directory
    bool SetWorkingPath(const std::string& path);

    // =========================
    // [EXECUTABLE PATH]
    // =========================

    // Full path to the executable
    std::string GetExecutablePath();

    // Directory where the executable resides
    std::string GetExecutableDirectory();

    // Directory static independetly of executable location
    std::string GetStaticDataDirectory();

    // Sets working directory to executable directory
    bool SetWorkingPathToExecutable();
}

#endif // PROCESS_HPP
