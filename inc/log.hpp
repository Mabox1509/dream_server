#ifndef _LOG_H
#define _LOG_H
//[INCLUDES]
#include <string>
#include <vector>
#include <chrono>
#include <cstdint>

//[NAMESPACE]
namespace Log
{
    //[TYPES]
    enum class Type : uint8_t
    {
        MESSAGE,
        WARNING,
        ERROR
    };
    typedef struct entry_t
    {
        Type type;
        std::chrono::system_clock::time_point timestamp;
        std::string message;
    } entry_t;

    //[FUNCTIONS]
    void Message(const std::string& _msg, ...);
    void Warning(const std::string& _msg, ...);
    void Error(const std::string& _msg, ...);

    const std::vector<entry_t>& GetEntries();
    void Clear();
}
#endif