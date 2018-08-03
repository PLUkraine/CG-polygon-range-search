#ifndef SCENEGENERATOR_H
#define SCENEGENERATOR_H

#include <random>

#include "geometrysearchlibrary_global.h"
#include "rangesearchdata.h"

class GEOMETRYSEARCHLIBRARYSHARED_EXPORT DataGenerator
{
public:
    DataGenerator();

    void generate(RangeSearchData &scene, int n, int k);
private:
    std::random_device rd;
    std::mt19937 mt;
};

#endif // SCENEGENERATOR_H
