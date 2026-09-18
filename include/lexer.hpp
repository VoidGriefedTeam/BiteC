#pragma once

#include <string>
#include <vector>
#include <fmt/color.h>
#include <fstream>

class Lexer
{
public:
    std::vector<std::string> tokenizeFile(const std::string& filepath);

private:
    std::ifstream openFile(const std::string& fullPath);
};