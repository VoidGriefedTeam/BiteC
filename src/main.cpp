#include <lexer.hpp>
#include <translator.hpp>
#include <CLI11/CLI11-main/include/CLI/CLI.hpp>

int main(int argc, char* argv[])
{
    fmt::print(fg(fmt::color::teal) | fmt::emphasis::bold, "_________\n"
                                                            "|  BiteC |\n"
                                                            "|________|\n");
    
    CLI::App app{"BiteC - BITE compiler"};

    std::string inputFile;

    app.add_option("file", inputFile, "BITE source file")
        ->required();

    CLI11_PARSE(app, argc, argv);

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
    }

    Translator Translate;
    Translate.translate(words);

}   