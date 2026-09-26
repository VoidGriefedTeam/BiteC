#include <linker.hpp>

void Linker::link(
    const std::string& outputFile,
    const std::string& os
)
{
    std::filesystem::path objectPath(outputFile);
    std::filesystem::path outputPath = objectPath;

    std::filesystem::path runtime =
        std::filesystem::current_path() / "runtime" / os;

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