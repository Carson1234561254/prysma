#include "Compilateur/LLVM/LlvmSerializer.h"

void LlvmSerializer::SauvegarderCodeLLVM(const string& path)
{
        llvm::raw_fd_ostream out(path, errorCode);
        _module.print(out, nullptr);
        out.close();
}