#pragma once

#include <string>
#include <filesystem>
#include <cstdlib>
#include <fmt/color.h>
#include <logger.hpp>
#include <process.h>
#include <cerrno>
#include <cstring>

class Linker
{
public:
    void link(const std::string& outputFile, const std::string& os);
private:
    void winlink(const std::filesystem::path& outputPath,
        const std::filesystem::path& objectPath,
        const std::filesystem::path& runtime);
    void linlink(const std::filesystem::path& outputPath,
        const std::filesystem::path& objectPath,
        const std::filesystem::path& runtime);
};
