#include <translator.hpp>

void Translator::var_create(const std::vector<std::string>& line)
{
    auto name = line[1].substr(1);
    auto type = variables[name].type;
    if (type == Type::Int)
    {
        llvm_variables[name] =
        builder.CreateAlloca(builder.getInt32Ty(), nullptr, name);
    }
    else if (type == Type::String)
    {
        llvm_variables[name] = builder.CreateAlloca(
            builder.getInt8Ty()->getPointerTo(),
            nullptr,
            name
        );
    }
}