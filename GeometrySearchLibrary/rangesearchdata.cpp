#include "rangesearchdata.h"


RangeSearchData::RangeSearchData()
{
    clear();
}

void RangeSearchData::clear()
{
    this->polygons.clear();
    this->points.clear();
    this->insidePoints.clear();
}
