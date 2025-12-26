#ifndef _CONSOLE_H
#define _CONSOLE_H
//[INCLUDES]
#include <string>
#include <vector>
#include <chrono>
#include <cstdint>

//[NAMESPACE]
namespace Console
{
    //[TYPES]
    enum class Color : uint8_t
    {
        WHITE,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        CYAN,
        MAGENTA,
        BRIGHT_BLACK,
        BRIGHT_WHITE,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_CYAN,
        BRIGHT_MAGENTA
    };
    typedef struct line_t
    {
        std::string text;
        Color color;
    } line_t;

    //[FUNCTIONS]
    void Print(const std::string& text, Color color = Color::WHITE, ...);
    void Clear();

    const std::vector<line_t>& GetBuffer();
}
#endif