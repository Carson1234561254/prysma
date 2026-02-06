#ifndef B7A1B053_311E_4DDE_9808_6B5699644912
#define B7A1B053_311E_4DDE_9808_6B5699644912
#include <string>

class ConstructeurSysteme
{
private:
    std::string _pathLib;
    std::string _libObjDir;
    std::string _outputLL;
    std::string _executable;
    static std::string parcourirEtCollecterFichiers(const std::string& repertoire, const std::string& extension);

public:
    ConstructeurSysteme(std::string pathLib, std::string libObjDir, std::string outputLL, std::string executable);
    ~ConstructeurSysteme();

    void lierLibExecutable();
    void compilerLib();
};

#endif /* B7A1B053_311E_4DDE_9808_6B5699644912 */
