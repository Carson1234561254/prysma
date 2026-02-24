#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudDeclarationVariable.h"
#include "Compilateur/AST/Registre/Pile/RegistreVariable.h"
#include "Compilateur/AST/Registre/Types/IType.h"
#include "Compilateur/Lexer/Lexer.h"

void VisiteurRemplissageRegistre::visiter(NoeudDeclarationVariable* noeudDeclarationVariable)
{
    Token token; 
    IType* type = noeudDeclarationVariable->getType();
    token.value = noeudDeclarationVariable->getNom();
   
    _contextGenCode->registreVariable->enregistrer(token, Symbole(nullptr, type));
}