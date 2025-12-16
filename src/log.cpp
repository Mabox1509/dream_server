// [INCLUDES]
#include "../inc/log.hpp"

#include <shared_mutex>
#include <cstdarg>
#include <cstdio>
#include <mutex>

// [NAMESPACE]
namespace Log
{
    // =========================
    // [PRIVATE DATA]
    // =========================
    static std::vector<entry_t> entries;
    static std::shared_mutex mutex;

    // =========================
    // [PRIVATE FUNCTIONS]
    // =========================
    static std::string Stringf(const std::string& fmt, va_list args)
    {
        va_list args_copy;
        va_copy(args_copy, args);

        int len = std::vsnprintf(nullptr, 0, fmt.c_str(), args_copy);
        va_end(args_copy);

        if (len <= 0)
            return {};

        std::string result;
        result.resize(len);

        std::vsnprintf(result.data(), len + 1, fmt.c_str(), args);
        return result;
    }
    static void AddLog(Type type, const std::string& fmt, va_list args)
    {
        entry_t e;
        e.type = type;
        e.timestamp = std::chrono::system_clock::now();
        e.message = Stringf(fmt, args);

        std::unique_lock lock(mutex);
        entries.emplace_back(std::move(e));
    }

    // =========================
    // [PUBLIC API]
    // =========================
    void Message(const std::string& _msg, ...)
    {
        va_list args;
        va_start(args, _msg);
        AddLog(Type::MESSAGE, _msg, args);
        va_end(args);
    }

    void Warning(const std::string& _msg, ...)
    {
        va_list args;
        va_start(args, _msg);
        AddLog(Type::WARNING, _msg, args);
        va_end(args);
    }

    void Error(const std::string& _msg, ...)
    {
        va_list args;
        va_start(args, _msg);
        AddLog(Type::ERROR, _msg, args);
        va_end(args);
    }

    const std::vector<entry_t>& GetEntries()
    {
        std::shared_lock lock(mutex);
        return entries;
    }

    void Clear()
    {
        std::unique_lock lock(mutex);
        entries.clear();
    }
}
