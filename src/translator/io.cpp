#include <translator.hpp>

void Translator::print(const std::vector<std::string>& line)
{
    auto value = line[1];

    if (value.empty())
        return;

    auto* printfType = llvm::FunctionType::get(
        builder.getInt32Ty(),
        builder.getInt8Ty()->getPointerTo(),
        true
    );

    auto printfFunc = module->getOrInsertFunction(
        "printf",
        printfType
    );

    if (value[0] == '&')
    {
        auto name = value.substr(1);

        auto type = variables[name].type;

        if (type == Type::Int)
        {
            auto* loaded = builder.CreateLoad(
                builder.getInt32Ty(),
                llvm_variables[name]
            );

            auto* format = builder.CreateGlobalString(
                "%d\n",
                "print_format",
                0,
                module.get()
            );

            auto* formatPtr = builder.CreateInBoundsGEP(
                format->getValueType(),
                format,
                {
                    builder.getInt32(0),
                    builder.getInt32(0)
                }
            );

            builder.CreateCall(
                printfFunc,
                {formatPtr, loaded}
            );
        }
    }
    else if (value.front() == '"' && value.back() == '"')
    {
        auto tvalue = value.substr(1, value.size() - 2);
        tvalue += '\n';

        auto* str = builder.CreateGlobalString(
            tvalue,
            "print_string",
            0,
            module.get()
        );

        auto* strPtr = builder.CreateInBoundsGEP(
            str->getValueType(),
            str,
            {
                builder.getInt32(0),
                builder.getInt32(0)
            }
        );

        builder.CreateCall(
            printfFunc,
            {strPtr}
        );
    }
}