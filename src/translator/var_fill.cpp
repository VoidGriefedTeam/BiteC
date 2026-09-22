#include <translator.hpp>

void Translator::var_fill(const std::vector<std::string>& line)
{
    auto name = line[0].substr(1);
    std::string value = line [2];
    auto type = variables[name].type;
    if (type == Type::Int)
    {
        auto vc = stoi(value);
        builder.CreateStore(
        builder.getInt32(vc),
        llvm_variables[name]
        );
    }
    else if (type == Type::String)
    {
        auto* str = builder.CreateGlobalString(
        value,
        "str",
        0,
        module.get()
        );

        builder.CreateStore(
            str,
            llvm_variables[name]
        );
    }
    
}