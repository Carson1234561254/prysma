#include "Compilateur/AST/ConstructeurArbreInstruction.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/GestionnaireErreur.h"
#include <vector>


ConstructeurArbreInstruction::ConstructeurArbreInstruction(RegistreInstruction* registreInstructions, llvm::BumpPtrAllocator& arena)
	: _arena(arena)
{
	_registreInstructions = registreInstructions;
}

ConstructeurArbreInstruction::~ConstructeurArbreInstruction()
{
}

INoeud* ConstructeurArbreInstruction::construire(std::vector<Token>& tokens, int& index)
{
    if (!_registreInstructions->existe(tokens[static_cast<size_t>(index)].type)) {
        throw ErreurCompilation("Instruction inconnue : '" + tokens[static_cast<size_t>(index)].value + "'", tokens[static_cast<size_t>(index)].ligne, tokens[static_cast<size_t>(index)].colonne);
    }
    IParseur* ParentNoeud = _registreInstructions->recuperer(tokens[static_cast<size_t>(index)].type);
    INoeud* enfant = ParentNoeud->parser(tokens, index);
    return enfant;
}

INoeud* ConstructeurArbreInstruction::construire(std::vector<Token>& tokens)
{
    int index = 0; 
    return construire(tokens, index);
}

llvm::BumpPtrAllocator& ConstructeurArbreInstruction::getArena()
{
    return _arena;
}