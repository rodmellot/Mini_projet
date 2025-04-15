
#ifndef AVERAGEPIXEL_H
#define AVERAGEPIXEL_H

#include "ComparaisonAlgorithm.h"
#include "DataBank.h"  

class AveragePixel : public ComparaisonAlgorithm {
public:
    AveragePixel(Databank& db);  
    void getDataForDay(const Date& date) override;  

private:
    Databank& databank;  
};

#endif /* AVERAGEPIXEL_H */
