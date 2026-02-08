#include "Compilateur/LLVM/LlvmBackend.h"
#include <llvm/Support/TargetSelect.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>
#include <vector>

using namespace llvm;

LlvmBackend::LlvmBackend() {

    _context = std::make_unique<LLVMContext>();
    _module = std::make_unique<Module>("output", *_context);
    _builder = std::make_unique<IRBuilder<NoFolder>>(*_context);

    // Initialisation de la cible (évite d'avoir des adresses mémoire aléatoires)
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();

    std::string targetTriple = sys::getDefaultTargetTriple();
    _module->setTargetTriple(targetTriple);
    
    std::string error;
    const auto *target = TargetRegistry::lookupTarget(targetTriple, error);
    if (target == nullptr) {
        errs() << error;
    }

    TargetOptions opt;
    target->createTargetMachine(targetTriple, "generic", "", opt, Reloc::Model::PIC_);
}



llvm::Value* LlvmBackend::creerAutoCast(llvm::Value* valeurSource, llvm::Type* typeCible)
{
    if (valeurSource->getType() == typeCible)
    {
        return valeurSource;
    }
    

    llvm::Instruction::CastOps opcode = llvm::CastInst::getCastOpcode(
        valeurSource, 
        true,       
        typeCible, 
        true      
    );

    return _builder->CreateCast(opcode, valeurSource, typeCible, "autocast");
}


void LlvmBackend::declarerExterne(const std::string& nom, llvm::Type* ret, std::vector<llvm::Type*>& args)
{
    llvm::FunctionType* type = llvm::FunctionType::get(ret, args, false);
    llvm::Function::Create(type, llvm::Function::ExternalLinkage, nom, *_module);
}

llvm::Value* LlvmBackend::chargerValeur(llvm::Value* adresseMemoire, const std::string& nomVariable)
{
    if (adresseMemoire == nullptr) 
    { 
        return nullptr;
    }

    if (auto* allocaInst = llvm::dyn_cast<llvm::AllocaInst>(adresseMemoire)) {
        
        llvm::Type* typeStocke = allocaInst->getAllocatedType();

        return _builder->CreateLoad(typeStocke, allocaInst, nomVariable);
    }
    return adresseMemoire;
}