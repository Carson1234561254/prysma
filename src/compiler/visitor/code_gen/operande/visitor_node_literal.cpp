#include "compiler/ast/ast_genere.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_type.h"
#include "compiler/visitor/code_gen/visitor_general_gen_code.h"
#include "compiler/ast/registry/types/type_simple.h"
#include "compiler/llvm/gestion_variable.h"
#include "compiler/visitor/code_gen/helper/error_helper.h"
#include <cstdint>
#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <string>

void GeneralVisitorGenCode::visiter(NodeLiteral* nodeLiteral)
{
    llvm::LLVMContext& context = _contextGenCode->getBackend()->getContext();
    Token token = nodeLiteral->getToken();

    if (token.type == TOKEN_IDENTIFIER) {
        VariableLoader loader(_contextGenCode);
        _contextGenCode->setTemporaryValue(loader.load(token.value));
        return; 
    }

    llvm::Value* llvmValue = nullptr;
    llvm::Type* llvmType = nullptr;

    if (token.type == TOKEN_TRUE || token.type == TOKEN_FALSE) {
        bool value = (token.type == TOKEN_TRUE);
        llvmType = llvm::Type::getInt1Ty(context);
        llvmValue = llvm::ConstantInt::get(llvmType, value ? 1 : 0);
    }
    else if (token.type == TOKEN_LIT_BOOL) {
        int value = std::stoi(token.value);
        llvmType = llvm::Type::getInt1Ty(context);
        llvmValue = llvm::ConstantInt::get(llvmType, value != 0 ? 1 : 0);
    }
    else if (token.type == TOKEN_LIT_INT) { 
        int value = std::stoi(token.value); 
        llvmType = llvm::Type::getInt32Ty(context);
        llvmValue = llvm::ConstantInt::get(llvmType, static_cast<uint64_t>(value), true);
    }
    else if (token.type == TOKEN_LIT_FLOAT) { 
        float value = std::stof(token.value); 
        llvmType = llvm::Type::getFloatTy(context);
        llvmValue = llvm::ConstantFP::get(llvmType, value);
    }
    else {
        ErrorHelper::compilationError("Unsupported literal type (" + token.value + ")");
    }

    _contextGenCode->setTemporaryValue(Symbol(llvmValue, _contextGenCode->getTemporaryValue().getType(), _contextGenCode->getTemporaryValue().getPointedElementType()));
    _contextGenCode->setTemporaryValue(Symbol(_contextGenCode->getTemporaryValue().getAddress(), new (_contextGenCode->getArena()->Allocate<TypeSimple>()) TypeSimple(llvmType), _contextGenCode->getTemporaryValue().getPointedElementType()));
}