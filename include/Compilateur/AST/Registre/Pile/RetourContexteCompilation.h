#ifndef D5D5CC5E_96E0_4410_95A8_57E0E7660888
#define D5D5CC5E_96E0_4410_95A8_57E0E7660888

#include "Compilateur/AST/Registre/Types/IType.h"
#include <memory>
#include <stack>
class RetourContexteCompilation
{
private:
    std::stack<std::shared_ptr<IType>> _contexte; 

public:

    RetourContexteCompilation()
    {}

    ~RetourContexteCompilation()
    {}

    std::shared_ptr<IType> recupererContext();
        
    void piler(std::shared_ptr<IType> token);
    void depiler();

};

#endif /* D5D5CC5E_96E0_4410_95A8_57E0E7660888 */
