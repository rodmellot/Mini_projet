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
    Date operator+= (int nbJour);
    Date operator++ ();
    //doit renvoyer True si d1 est avant d2
    bool operator<(const Date& other) const;
    //doit renvoyer True si d1 est égal à d2
    bool operator== (const Date& other) const;
};

// opérateur affichage 
std::ostream& operator<<(std::ostream& os, const Date& d);