#include <translator.hpp>

void Translator::translate(const std::vector<std::string>& stream)
{
    auto line_words = cutils::break_lines(stream);
    
    for (size_t i = 0; i < line_words.size(); i++)
    {
        auto intent = cutils::detect_intent(line_words[i]);
        if (intent == "VAR_SET")
        {
           std::string ir =
            "%var = alloca i32\n"
            "store i32 data, ptr %var";

            auto var_name = line_words[i][1];
            if (!var_name.empty() && var_name[0] == '&')
            {
                var_name.erase(0, 1);
            }
            std::string one = cutils::replace(var_name, "var", ir);
            
            auto data = line_words[i][3];
            auto two = cutils::replace(data, "data", one);
            fmt::print("{}",two);
        }
    }

}