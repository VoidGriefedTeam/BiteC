#include <lexer.hpp>
#include <translator.hpp>
#include <CLI11/CLI11-main/include/CLI/CLI.hpp>
#include <object.hpp>
#include <cstdlib>
#include <fmt/color.h>
#include <linker.hpp>
#include <logger.hpp>
#include <chrono>

bool Logger::verbose = false;
int main(int argc, char** argv)
{   
    auto start = std::chrono::steady_clock::now();
    fmt::print(fg(fmt::color::teal) | fmt::emphasis::bold, "_________\n"
                                                            "|  BiteC |\n"
                                                            "|________|\n");
    
                                                            if (argc == 2 &&
    (std::strcmp(argv[1], "--version") == 0 ||
     std::strcmp(argv[1], "-V") == 0))
    {
        fmt::print(
            "BiteC - Official Bite Compiler\n"
            "Version 1.2.1 -- Chewer\n"
        );

        return 0;
    }

    CLI::App app{"BiteC - BITE compiler"};

    std::string inputFile;
    std::string current_os;
    bool obj = false;
    std::string outputFile;
    app.add_option("file", inputFile, "BITE source file")
        ->required();
    app.add_option("OS", current_os, "The OS which would be used for running the program")
        ->required();
    app.add_flag("--verbose", Logger::verbose, "Show Detailed Info");
    app.add_option("-o,--output", outputFile, "Output object file")
        ->required();

    CLI11_PARSE(app, argc, argv);
    if (outputFile.empty())
    {
        outputFile = "output.obj";
    }

    verbose(fmt::emphasis::bold, "Parsing file: ");
    Lexer lexer;
    std::vector<std::string> words;
    words = lexer.tokenizeFile(inputFile);
    if (!words.empty())
    {
        verbose(fg(fmt::terminal_color::green) , "Done ✅\n");
    }
    if (words.empty())
    {
        verbose(fg(fmt::terminal_color::red), "Failed ❌\n");
        if (Logger::verbose != true)
        {
            fmt::println(fg(fmt::terminal_color::red), "Parsing: Failed ❌\n");
        }
        std::exit(3);
    }
    verbose("Translating: ");
    Translator Translate;
    Translate.translate(words);
    verbose(fg(fmt::terminal_color::green), "Done ✅\n");
    verbose("Creating Object File: ");
    ObjectCompiler compiler;
    compiler.generate(
        Translate.get_module(),
        outputFile,
        current_os
    );
    verbose(fg(fmt::terminal_color::green), "Done ✅\n");
    
    if (!obj) {
    Linker linked;
    linked.link(outputFile,current_os);
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        ).count();

    fmt::print(fg(fmt::terminal_color::green), "Build Successful ✅🎉\n");
    verbose("Time: {} ms\n", elapsed);
}