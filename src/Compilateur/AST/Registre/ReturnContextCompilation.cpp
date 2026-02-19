#include "Compilateur/AST/Registre/Pile/RetourContexteCompilation.h"
#include <stack>
#include <stdexcept>


std::shared_ptr<IType> RetourContexteCompilation::recupererContext()
{
    return _contexte.top();
}

void RetourContexteCompilation::piler(std::shared_ptr<IType> token)
{
    _contexte.push(token);
}

void RetourContexteCompilation::depiler()
{
    if(_contexte.empty())
    {
        throw std::runtime_error("La pile est déjà vide! ");
    }
    _contexte.pop();
}