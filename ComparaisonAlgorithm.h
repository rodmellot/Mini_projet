#ifndef COMPARISONALGORITHM_H
#define COMPARISONALGORITHM_H

#include <string>
#include "Date.h"

class ComparaisonAlgorithm {
public:
    virtual ~ComparaisonAlgorithm() = default;

    // Méthode à implementer a posteriori dans les classes filles
    virtual void getDataForDay(const Date& date) = 0;
};

#endif /* COMPARISONALGORITHM_H */
