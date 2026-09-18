#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <fmt/color.h>
#include <unordered_set>
#include <CompilerUtils/include/CompilerUtils.hpp>

class Translator
{
    public:
    void translate(const std::vector<std::string>& stream);
    private:
    std::string detect_intent(const std::vector<std::string>& words);
    void LLVMCompile();
};