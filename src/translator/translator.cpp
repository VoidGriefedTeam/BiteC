#include <translator.hpp>

Translator::Translator()
    : context(),
      module(std::make_unique<llvm::Module>("BiteModule", context)),
      builder(context)
{
    auto* functionType = llvm::FunctionType::get(
        builder.getInt32Ty(),
        false
    );

    auto* mainFunction = llvm::Function::Create(
        functionType,
        llvm::Function::ExternalLinkage,
        "main",
        module.get()
    );

    auto* entry = llvm::BasicBlock::Create(
        context,
        "entry",
        mainFunction
    );
    llvm::FunctionType* scanfType =
    llvm::FunctionType::get(
        builder.getInt32Ty(),
        {builder.getInt8Ty()->getPointerTo()},
        true
    );

    scanfFunc = module->getOrInsertFunction(
    "scanf",
    scanfType
    );

    builder.SetInsertPoint(entry);
    
}

void Translator::translate(const std::vector<std::string>& stream)
{
    auto line_words = cutils::break_lines(stream);
    
    for (size_t i = 0; i < line_words.size(); i++)
    {
        auto intent = cutils::detect_intent(line_words[i], i);
        if (intent == "VAR_CR")
        {
            
            var_create(line_words[i]);  
        }
        else if (intent == "VAR_FILL")
        {
            var_fill(line_words[i]);
        }
        else if (intent == "PRINT")
        {
            
            print(line_words[i]);
        }
        else if (intent == "READ")
        {
            
            read(line_words[i]);
        }
        else
        {
            
        }

    }
    builder.CreateRet(builder.getInt32(0));
}

llvm::Module& Translator::get_module()
{
    return *module;
}

