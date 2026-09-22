#pragma once

#include <string>
#include <filesystem>
#include <cstdlib>
#include <fmt/color.h>

class Linker
{
public:
    void link(const std::string& outputFile);
};
