#include <iostream>
#include <string>

class Date{
    private:
    int d_annee;
    int d_mois;
    int d_jour;

    public:
    //constructeur
    Date(int annee, int mois, int jour);

    //getter
    int getAnnee() const;
    int getMois() const;
    int getJour() const;

    //setter
    void setAnnee(int annee);
    void setMois(int mois);
    void setJour(int jour);

    //opération
    Date operator+ (int nbJour) const;

};

// opérateur affichage 
std::ostream& operator<<(std::ostream& os, const Date& d);