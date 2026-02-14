#ifndef ECD975BF_C219_4D88_AC4A_B12DE1902F2B
#define ECD975BF_C219_4D88_AC4A_B12DE1902F2B

#include <string>
#include <sstream>

class SortieGrapheVisuelTexte
{
private:    
    std::string _cheminSortie;
    std::stringstream _contenuGraphe;
    int _compteurId;

public:
    SortieGrapheVisuelTexte(const std::string& cheminSortie);
    void ajouterNoeudValeur(int noeudId, const std::string& valeur);
    void ajouterNoeudOperation(int noeudId, const std::string& operateur);
    void ajouterArete(int parentId, int enfantId);
    void generer();
    int obtenirNouvelId();
};

#endif /* ECD975BF_C219_4D88_AC4A_B12DE1902F2B */
