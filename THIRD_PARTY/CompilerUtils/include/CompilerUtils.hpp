#pragma once

#include <string>
#include <vector>
#include <fmt/color.h>
#include <unordered_set>
#include <unordered_map>
#include <cstdlib>

enum class Type
{
    Int,
    Float,
    String,
    Double,
    Unknown
};

struct Variable
{
    Type type;
};

extern const std::unordered_set<std::string> types;
extern std::unordered_map<std::string, Variable> variables;

namespace cutils
{
    Type get_type(const std::string& type);
    std::string replace(
        const std::string& true_value,
        const std::string& replace_key,
        std::string string
    );

    std::vector<std::vector<std::string>> break_lines(
        const std::vector<std::string>& words
    );

    std::string detect_intent(const std::vector<std::string>& words, const int& i);
}