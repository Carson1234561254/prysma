#ifndef LLVMSERIALIZER_H
#define LLVMSERIALIZER_H

#include <llvm-18/llvm/Support/raw_ostream.h>
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include <string>

using namespace llvm;
using namespace std;

class LlvmSerializer {
    private: 
        Module& _module;
        error_code errorCode;
            
    public: 
        LlvmSerializer(Module& mod) : _module(mod) {}
        void SauvegarderCodeLLVM(const string& path);
};

#endif /* LLVMSERIALIZER_H */