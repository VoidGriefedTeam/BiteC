#include <lexer.hpp>
#include <translator.hpp>
#include <CLI11/CLI11-main/include/CLI/CLI.hpp>
#include <object.hpp>
#include <cstdlib>
#include <fmt/color.h>
#include <linker.hpp>

int main(int argc, char** argv)
{
    fmt::print(fg(fmt::color::teal) | fmt::emphasis::bold, "_________\n"
                                                            "|  BiteC |\n"
                                                            "|________|\n");
    
    CLI::App app{"BiteC - BITE compiler"};

    std::string inputFile;
    std::string current_os;
    bool version = false;
    std::string outputFile;

    app.add_option("file", inputFile, "BITE source file")
        ->required();
    app.add_option("OS", current_os, "The OS which would be used for running the program")
        ->required();
    app.add_flag("--version, -V", version, "Show Version Info");
    app.add_option("-o,--output", outputFile, "Output object file")
        ->required();

    CLI11_PARSE(app, argc, argv);
    
    if (version){
        fmt::print("BiteC - Official Bite Compiler\n"
                   "1.2.1 -- Chewer\n");
    }
    if (outputFile.empty())
    {
        outputFile = "output.obj";
    }

    fmt::print(fmt::emphasis::bold, "Parsing file: ");
    Lexer lexer;
    std::vector<std::string> words;
    words = lexer.tokenizeFile(inputFile);
    if (!words.empty())
    {
        fmt::print(fg(fmt::color::green) , "Done ✅\n");
    }
    if (words.empty())
    {
        fmt::print(fg(fmt::color::red), "Failed ❌\n");
        std::exit(3);
    }

    Translator Translate;
    Translate.translate(words);

    ObjectCompiler compiler;
    compiler.generate(
        Translate.get_module(),
        outputFile,
        current_os
    );

    Linker linked;
    linked.link(outputFile);
}