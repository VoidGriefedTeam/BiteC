#include <lexer.hpp>

std::ifstream Lexer::openFile(const std::string& FullPath)
{
    std::ifstream file(FullPath);

    if (!file.is_open())
    {
        fmt::print(
            fg(fmt::color::red) | fmt::emphasis::bold,
            "ERROR: could not open file: {}",
            FullPath
        );
    }

    return file;
}

std::vector<std::string> Lexer::tokenizeFile(const std::string& filepath)
{
    std::ifstream file = openFile(filepath);

    std::vector<std::string> words;
    std::string word;

    while (file >> word)
    {
        words.push_back(word);
    }

    return words;
}