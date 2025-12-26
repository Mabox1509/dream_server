// [INCLUDES]
#include "../../inc/utils/log.hpp"
#include "../../inc/console.hpp"

#include <cstdarg>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

// [NAMESPACE]
namespace Log
{
    // =========================
    // [PRIVATE HELPERS]
    // =========================
    static std::string Stringf(const std::string& fmt, va_list args)
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

    static std::string TimeNow()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        return oss.str();
    }

    static void PrintLog(
        const char* type,
        Console::Color color,
        const std::string& fmt,
        va_list args)
    {
        std::string message = Stringf(fmt, args);

        std::ostringstream oss;
        oss << "[" << TimeNow() << "]"
            << "[" << type << "]: "
            << message;

        Console::Print(oss.str(), color);
    }

    // =========================
    // [PUBLIC API]
    // =========================
    void Message(const std::string& _msg, ...)
    {
        va_list args;
        va_start(args, _msg);
        PrintLog("MESSAGE", Console::Color::WHITE, _msg, args);
        va_end(args);
    }

    void Warning(const std::string& _msg, ...)
    {
        va_list args;
        va_start(args, _msg);
        PrintLog("WARNING", Console::Color::YELLOW, _msg, args);
        va_end(args);
    }

    void Error(const std::string& _msg, ...)
    {
        va_list args;
        va_start(args, _msg);
        PrintLog("ERROR", Console::Color::BRIGHT_RED, _msg, args);
        va_end(args);
    }
}
