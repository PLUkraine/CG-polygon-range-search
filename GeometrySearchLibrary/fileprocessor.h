#ifndef POLYGONFILE_H
#define POLYGONFILE_H

#include <QObject>
#include <QString>

#include "rangesearchdata.h"
#include "geometrysearchlibrary_global.h"

class GEOMETRYSEARCHLIBRARYSHARED_EXPORT FileProcessor
{
public:
    bool read(RangeSearchData& scene, const char *filename);
    bool write(RangeSearchData& scene, const char *filename);

    QString getError() const;

private:
    QString m_errorMessage;
};

#endif // POLYGONFILE_H
