#include <CompilerUtils.hpp>

const std::unordered_set<std::string> types = 
{
    "_INT",
    "_FLO",
    "_DOU",
    "_STR"
};

std::unordered_map<std::string, Variable> variables;

namespace cutils
{
    Type get_type(const std::string& type)
    {
        if (type == "_INT")
            return Type::Int;

        else if (type == "_FLO")
            return Type::Float;

        else if (type == "_STR")
            return Type::String;

        else if (type == "_DOU")
            return Type::Double;
        else 
            return Type::Unknown;
    }

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
        std::vector<std::vector<std::string>> lines;
        std::vector<std::string> current_line;

        bool in_quotes = false;
        std::string quoted_string;

        for (const auto& word : copy)
        {
            for (char c : word)
            {
                if (c == '"')
                {
                    in_quotes = !in_quotes;
                    quoted_string += c;
                }
                else
                {
                    quoted_string += c;
                }
            }

            if (!in_quotes)
            {
                current_line.push_back(quoted_string);
                quoted_string.clear();

                if (word == ";")
                {
                    lines.push_back(current_line);
                    current_line.clear();
                }
            }
            else
            {
                quoted_string += ' ';
            }
        }

        if (!quoted_string.empty())
        {
            current_line.push_back(quoted_string);
        }

        return lines;
    }

    std::string detect_intent(const std::vector<std::string>& words, const int& i)
    {
        if (words[0] == "PRINT" && words[2] == ";")
            {
            return "PRINT";
            }  
        else if (words[1] == "_READ")
        {
            return "READ";
        }
        else if (
        !words[1].empty() &&
        words[1][0] == '&' &&
        words[2] == ";"
        ) 
        {
           
            auto type = cutils::get_type(words[0]);
            if (type == Type::Unknown)
            {
                fmt::println(fg(fmt::terminal_color::red)| fmt::emphasis::bold, "Unknown Variable Type. Line{}", i);
                fmt::println(fg(fmt::terminal_color::red)| fmt::emphasis::blink, "Unrecognized Variable Type :{}", words[0]);
                std::exit(1);
            }
            auto n = words[1].substr(1);
            variables[n] = {type};
        
            return "VAR_CR";
        }
        else if (variables.contains(words[0].substr(1)) &&
        words[1] == "_VAL" &&
        words[3] == ";") 
        {
            return "VAR_FILL";
        }
        else if (words[0] == "PRINT" && words[2] == ";")
        {
            return "PRINT";
        }
        else if (words[1] == "_READ")
        {
            return "READ";
        }
        else
        {
            return "Unknown";
        }
    }
}
