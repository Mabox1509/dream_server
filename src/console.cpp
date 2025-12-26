// [INCLUDES]
#include "../inc/console.hpp"
#include "../inc/utils/process.hpp"

#include <cstdarg>
#include <cstdio>
#include <mutex>
#include <iostream>

// [NAMESPACE]
namespace Console
{
    #define MAX_BUFFER_LINES 1000

    // =========================
    // [PRIVATE DATA]
    // =========================
    static std::vector<line_t> buffer;
    static std::mutex mutex;

    // =========================
    // [PRIVATE HELPERS]
    // =========================
    static const char* ColorToAnsi(Color color)
    {
        switch (color)
        {
            case Color::WHITE:           return "\033[37m";
            case Color::RED:             return "\033[31m";
            case Color::GREEN:           return "\033[32m";
            case Color::YELLOW:          return "\033[33m";
            case Color::BLUE:            return "\033[34m";
            case Color::CYAN:            return "\033[36m";
            case Color::MAGENTA:         return "\033[35m";
            case Color::BRIGHT_BLACK:    return "\033[90m";
            case Color::BRIGHT_WHITE:    return "\033[97m";
            case Color::BRIGHT_RED:      return "\033[91m";
            case Color::BRIGHT_GREEN:    return "\033[92m";
            case Color::BRIGHT_YELLOW:   return "\033[93m";
            case Color::BRIGHT_BLUE:     return "\033[94m";
            case Color::BRIGHT_CYAN:     return "\033[96m";
            case Color::BRIGHT_MAGENTA:  return "\033[95m";
            default:                     return "\033[37m";
        }
    }

    static std::string vformat(const std::string& fmt, va_list args)
    {
        va_list copy;
        va_copy(copy, args);

        int len = std::vsnprintf(nullptr, 0, fmt.c_str(), copy);
        va_end(copy);

        if (len <= 0)
            return {};

        std::string result;
        result.resize(len);

        std::vsnprintf(result.data(), len + 1, fmt.c_str(), args);
        return result;
    }

    // =========================
    // [PUBLIC API]
    // =========================
    void Print(const std::string& text, Color color, ...)
    {
        va_list args;
        va_start(args, color);
        std::string formatted = vformat(text, args);
        va_end(args);

        {
            std::lock_guard lock(mutex);
            buffer.push_back({ formatted, color });

            if( buffer.size() > MAX_BUFFER_LINES )
            {
                buffer.erase(buffer.begin(), buffer.begin() + (buffer.size() - MAX_BUFFER_LINES));
            }
        }

        // Print to real console ONLY if possible
        if (Process::HasTerminal() && Process::IsForeground())
        {
            std::cout
                << ColorToAnsi(color)
                << formatted
                << "\033[0m"
                << std::endl;
        }
    }

    void Clear()
    {
        std::lock_guard lock(mutex);
        buffer.clear();

        if (Process::HasTerminal() && Process::IsForeground())
        {
            std::system("clear");
        }
    }

    const std::vector<line_t>& GetBuffer()
    {
        return buffer;
    }
}
