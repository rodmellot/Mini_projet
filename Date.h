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
    Date operator+ (const Date& d ,int nbJour);
    Date operator+= (Date& d ,int nbJour);
    Date operator++ (Date& d);
    //doit renvoyer True si d1 est avant d2
    bool operator< (const Date& d1, const Date& d2);
    //doit renvoyer True si d1 est égal à d2
    bool operator== (const Date& d1, const Date& d2);
};

// opérateur affichage 
std::ostream& operator<<(std::ostream& os, const Date& d);