#ifndef EEA73704_BBAE_43AD_9799_F1F919E04250
#define EEA73704_BBAE_43AD_9799_F1F919E04250

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"
#include "llvm/Support/Allocator.h"
#include <cstddef>
#include <memory>
#include <new>
#include <utility>

class IConstructeurArbre
{
public:
    virtual ~IConstructeurArbre() = default;
    virtual INoeud* construire(std::vector<Token>& tokens) = 0;
    virtual INoeud* construire(std::vector<Token>& tokens, int& index) = 0;
    virtual llvm::BumpPtrAllocator& getArena() = 0;

    template<typename T, typename... Args>
    T* allouer(Args&&... args) {
        void* mem = getArena().Allocate(sizeof(T), alignof(T));
        return new (mem) T(std::forward<Args>(args)...);
    }

    void* operator new(size_t taille, llvm::BumpPtrAllocator& arena) {
        return arena.Allocate(taille, 8); 
    }
};

#endif /* EEA73704_BBAE_43AD_9799_F1F919E04250 */
