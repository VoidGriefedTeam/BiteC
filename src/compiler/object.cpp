#include <object.hpp>

void ObjectCompiler::generate(
    llvm::Module& module,
    const std::string& output,
    const std::string& ost
)
{
    LLVMInitializeX86TargetInfo();
    LLVMInitializeX86Target();
    LLVMInitializeX86TargetMC();
    LLVMInitializeX86AsmPrinter();

    LLVMInitializeAArch64TargetInfo();
    LLVMInitializeAArch64Target();
    LLVMInitializeAArch64TargetMC();
    LLVMInitializeAArch64AsmPrinter();
    std::filesystem::path outputFile = output;
    auto objpath = outputFile.string();

    std::string target_triple_str;
    if (ost == "windows")
    {
        target_triple_str = "x86_64-w64-windows-gnu";
    }
    else if (ost == "linux64")
    {
        target_triple_str = "x86_64-pc-linux-gnu";
    }
    else if (ost == "macos")
    {
        target_triple_str = "arm64-apple-macos";
    }
    else if (ost == "android")
    {
        target_triple_str = "aarch64-linux-android";
    }
    else
    {
    llvm::errs() << "Unknown target OS: "
                 << ost << '\n';

    std::exit(58);
    }
    llvm::Triple target_triple(target_triple_str);
    module.setTargetTriple(target_triple);

    std::string error;
    const llvm::Target* target =
        llvm::TargetRegistry::lookupTarget(
            target_triple,
            error
        );

    if (!target)
    {
        llvm::errs()
            << "Target lookup failed: "
            << error
            << '\n';

        std::exit(68);
    }
    llvm::TargetOptions options;

    std::unique_ptr<llvm::TargetMachine> targetMachine =
        std::unique_ptr<llvm::TargetMachine>(
            target->createTargetMachine(
                target_triple,
                "generic",
                "",
                options,
                std::nullopt
            )
        );

    if (!targetMachine)
    {
        llvm::errs()
            << "Could not create target machine\n";

        std::exit(69);
    }

    module.setDataLayout(
        targetMachine->createDataLayout()
    );

    std::error_code errorCode;
    if (Logger::verbose){
    llvm::outs() << objpath
                << '\n';
    }
    llvm::raw_fd_ostream objectFile(
        objpath,
        errorCode,
        llvm::sys::fs::OF_None
    );

    if (errorCode)
    {
        llvm::errs()
            << "Could not open output file: "
            << errorCode.message()
            << '\n';

        std::exit(70);
    }

    llvm::legacy::PassManager passManager;

    if (targetMachine->addPassesToEmitFile(
            passManager,
            objectFile,
            nullptr,
            llvm::CodeGenFileType::ObjectFile
        ))
    {
        llvm::errs()
            << "Target cannot emit object files\n";

        std::exit(71);
    }

    passManager.run(module);

    objectFile.flush();
}
