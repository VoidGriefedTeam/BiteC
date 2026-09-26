#pragma once

#include <fmt/color.h>
#include <fmt/format.h>
#include <utility>

class Logger
{
public:
    static bool verbose;

    // Normal verbose output
    template<typename... Args>
    static void verbose_print(
        fmt::format_string<Args...> format,
        Args&&... args)
    {
        if (verbose)
            fmt::print(format, std::forward<Args>(args)...);
    }

    // Styled verbose output
    template<typename... Args>
    static void verbose_print(
        fmt::text_style style,
        fmt::format_string<Args...> format,
        Args&&... args)
    {
        if (verbose)
            fmt::print(style, format, std::forward<Args>(args)...);
    }
};

#define verbose(...) Logger::verbose_print(__VA_ARGS__)