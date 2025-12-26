// [INCLUDES]
#include "../../inc/utils/process.hpp"

#include <unistd.h>
#include <termios.h>
#include <limits.h>
#include <cstdlib>

#include "../../inc/utils/filesys.hpp"

//[VARIABLES]
const std::string static_path = "/mnt/storage/appdata/dream_server";


// [NAMESPACE]
namespace Process
{
    void Setup()
    {
        SetWorkingPathToExecutable();

        if(!FileSys::DirectoryExists(static_path))
            FileSys::CreateDirectory(static_path);

    }

    // =========================
    // [BASIC INFO]
    // =========================
    int GetPID()
    {
        return getpid();
    }

    int GetParentPID()
    {
        return getppid();
    }

    int GetProcessGroupID()
    {
        return getpgrp();
    }

    // =========================
    // [FOREGROUND / BACKGROUND]
    // =========================
    bool HasTerminal()
    {
        return isatty(STDIN_FILENO);
    }

    bool IsForeground()
    {
        if (!HasTerminal())
            return false;

        return getpgrp() == tcgetpgrp(STDIN_FILENO);
    }

    // =========================
    // [TERMINATION]
    // =========================
    [[noreturn]] void Terminate(int exit_code)
    {
        _exit(exit_code);
    }

    // =========================
    // [WORKING DIRECTORY]
    // =========================
    std::string GetWorkingPath()
    {
        char buffer[PATH_MAX];
        if (getcwd(buffer, sizeof(buffer)))
            return buffer;

        return {};
    }

    bool SetWorkingPath(const std::string& path)
    {
        return chdir(path.c_str()) == 0;
    }

    // =========================
    // [EXECUTABLE PATH]
    // =========================
    std::string GetExecutablePath()
    {
        char buffer[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);

        if (len <= 0)
            return {};

        buffer[len] = '\0';
        return buffer;
    }

    std::string GetExecutableDirectory()
    {
        std::string path = GetExecutablePath();
        if (path.empty())
            return {};

        size_t pos = path.find_last_of('/');
        if (pos == std::string::npos)
            return {};

        return path.substr(0, pos);
    }

    std::string GetStaticDataDirectory()
    {
        return static_path + "/";
    }

    bool SetWorkingPathToExecutable()
    {
        std::string dir = GetExecutableDirectory();
        if (dir.empty())
            return false;

        return SetWorkingPath(dir);
    }
}
