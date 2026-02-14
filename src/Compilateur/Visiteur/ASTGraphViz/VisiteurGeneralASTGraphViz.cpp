#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"

VisiteurGeneralGraphViz::VisiteurGeneralGraphViz(std::shared_ptr<ContextGenCode> contextGenCode) 
{}

VisiteurGeneralGraphViz::~VisiteurGeneralGraphViz()
{}


void VisiteurGeneralGraphViz::parcourirEnfant(NoeudInstruction* noeud)
{
     
}

llvm::Value* VisiteurGeneralGraphViz::evaluerExpression(std::shared_ptr<INoeud>& expression) {

}

void VisiteurGeneralGraphViz::visiter(NoeudLitteral* noeudLitteral)
{

}

