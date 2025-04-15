#ifndef SIMPLEPIXEL_H
#define SIMPLEPIXEL_H

#include "ComparisonAlgorithm.h"
#include "Databank.h"  

class SimplePixel : public ComparisonAlgorithm {
public:
    SimplePixel(Databank& db);  // Constructeur
    void getDataForDay(const Date& date) override;  

private:
    Databank& databank;  
};

#endif /* SIMPLEPIXEL_H */
