#ifndef _LOG_H
#define _LOG_H
//[INCLUDES]
#include <string>
#include <vector>
#include <chrono>
#include <cstdint>

//DEFS
#define LOG_MESSAGE(fmt, ...) \
    Log::Message("[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define LOG_WARNING(fmt, ...) \
    Log::Warning("[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    Log::Error("[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)


//[NAMESPACE]
namespace Log
{
    //[FUNCTIONS]
    void Message(const std::string& _msg, ...);
    void Warning(const std::string& _msg, ...);
    void Error(const std::string& _msg, ...);
}
#endif