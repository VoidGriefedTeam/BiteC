#pragma once

#include <string>
#include <vector>
#include <fmt/color.h>
#include <unordered_set>

extern const std::unordered_set<std::string> types;

namespace cutils
{
    std::string replace(
        const std::string& true_value,
        const std::string& replace_key,
        std::string string
    );

    std::vector<std::vector<std::string>> break_lines(
        const std::vector<std::string>& words
    );

    std::string detect_intent(const std::vector<std::string>& words);
}