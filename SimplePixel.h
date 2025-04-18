#ifndef SIMPLEPIXEL_H
#define SIMPLEPIXEL_H

#include "ComparaisonAlgorithm.h"
#include "DataBank.h"  

class SimplePixel : public ComparaisonAlgorithm {
public:
    SimplePixel(Databank& db);  // Constructeur
    void getDataForDay(const Date& date) override;  

private:
    Databank& databank;  
};

#endif /* SIMPLEPIXEL_H */
