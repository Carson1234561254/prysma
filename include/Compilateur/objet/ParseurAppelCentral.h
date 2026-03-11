#ifndef PARSEUR_APPELCENTRAL_H
#define PARSEUR_APPELCENTRAL_H

#include "Compilateur/AST/Registre/ContextParseur.h"
#include "Compilateur/AnalyseSyntaxique/Interfaces/IParseur.h"

class ParseurAppelCentral : public IParseur
{
private:
    ContextParseur& _contextParseur;

public:
    explicit ParseurAppelCentral(ContextParseur& contextParseur);
    ~ParseurAppelCentral() override;

    INoeud* parser(std::vector<Token>& tokens, int& index) override;
};

#endif /* PARSEUR_APPELCENTRAL_H */