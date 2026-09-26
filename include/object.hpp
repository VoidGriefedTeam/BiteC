#pragma once

#include <string>
#include <filesystem>
#include <cstdlib>

#include <llvm/IR/Module.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/TargetParser/Triple.h>

#include <logger.hpp>


class ObjectCompiler
{
public:
    void generate(llvm::Module& module, const std::string& output, const std::string& ost);
};