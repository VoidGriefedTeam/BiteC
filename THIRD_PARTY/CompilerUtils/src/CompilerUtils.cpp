#include <CompilerUtils.hpp>

const std::unordered_set<std::string> types = 
{
    "_INT",
    "_FLO",
    "_DOU",
    "_STR"
};
namespace cutils
{
    std::string replace(
        const std::string& true_value,
        const std::string& replace_key,
        std::string string
    )
    {
        std::size_t position = 0;

        while ((position = string.find(replace_key, position)) != std::string::npos)
        {
            string.replace(position, replace_key.length(), true_value);
            position += true_value.length();
        }

        return string;
    }

    std::vector<std::vector<std::string>> break_lines(
        const std::vector<std::string>& copy
    )
    {
        auto words = copy;
        std::vector<std::vector<std::string>> lines;
        std::vector<std::string> current_line;

        for (const auto& word : words)
        {
            current_line.push_back(word);

            if (word == ";")
            {
                lines.push_back(current_line);
                current_line.clear();
            }
        }

        words.clear();

        return lines;
    }

    std::string detect_intent(const std::vector<std::string>& words)
    {
        
        if (types.contains(words[0]) &&
        !words[1].empty() &&
        words[1][0] == '&' &&
        words[2] == "_VAL" &&
        words[4] == ";") 
        {
            return "VAR_SET";
        }
    }
}