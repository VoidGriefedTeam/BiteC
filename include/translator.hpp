#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CompilerUtils.hpp>

class Translator 
{
    public:
        Translator();
        void translate(const std::vector<std::string>& stream);
        llvm::Module& get_module();
    private:
        llvm::LLVMContext context;
        llvm::IRBuilder<> builder;
        std::unique_ptr<llvm::Module> module;

        std::unordered_map<std::string, llvm::Value*> llvm_variables;


        void var_create(const std::vector<std::string>& line);
        void var_fill(const std::vector<std::string>& line);
        void print(const std::vector<std::string>& line);

};

