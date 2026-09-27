#include <linker.hpp>
#include <windows.h>

std::filesystem::path executable_directory()
{
    wchar_t buffer[MAX_PATH];

    DWORD length = GetModuleFileNameW(
        nullptr,
        buffer,
        MAX_PATH
    );

    if (length == 0)
        std::exit(78);

    return std::filesystem::path(
        buffer,
        buffer + length
    ).parent_path();
}

void Linker::link(
    const std::string& outputFile,
    const std::string& os
)
{
    std::filesystem::path objectPath(outputFile);
    std::filesystem::path outputPath = objectPath;

    std::filesystem::path runtime =
            executable_directory() / "runtime" / os;

    if (os == "windows")
    {
        outputPath.replace_extension(".exe");
        winlink(outputPath, objectPath, runtime);
    }
    else if (os == "linux64")
    {
        outputPath.replace_extension("");
        linlink(outputPath, objectPath, runtime);
    }
    else {
    fmt::print(
        fg(fmt::terminal_color::red),
        "Unsupported target OS: {}\n",
        os
    );
    }   
}