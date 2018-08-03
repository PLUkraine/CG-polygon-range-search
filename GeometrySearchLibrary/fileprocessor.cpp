#include "fileprocessor.h"

#include <fstream>


bool FileProcessor::read(RangeSearchData& scene, const char *filename)
{
    // clear scene and error message
    scene.clear();
    m_errorMessage = "";

    // open file
    std::ifstream fin;
    fin.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try {
        fin.open(filename);

        // read points
        // read number of points
        size_t numberOfPoints = 0;
        fin >> numberOfPoints;
        // read every point
        while (numberOfPoints-- > 0) {
            Point p;
            fin >> p.x >> p.y;
            scene.points.push_back(p);
        }

        // read polygon
        // read number of points in the polygon
        size_t numberOfPolygonPoints = 0;
        fin >> numberOfPolygonPoints;
        std::vector<Point> polygonPoints;
        while (numberOfPolygonPoints-- > 0) {
            Point p;
            fin >> p.x >> p.y;
            polygonPoints.push_back(p);
        }
        scene.polygons.push_back(Polygon(polygonPoints));
    } catch (std::exception& ex) {
        m_errorMessage = "File \"" + QString(filename) + "\" is corrupted or missing";
        return false;
    }

    return true;
}

bool FileProcessor::write(RangeSearchData &scene, const char *filename)
{
    // clear error message
    m_errorMessage = "";

    // open file
    std::ofstream fout;
    fout.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try {
        fout.open(filename);

        // write points
        // write number of points
        fout << scene.points.size() << std::endl;
        // read every point
        for (size_t i=0; i<scene.points.size(); ++i ) {
            Point p = scene.points[i];
            fout << p.x << " " << p.y << std::endl;
        }
        fout << std::endl;

        // write polygon
        // write number of points in the polygon
        fout << scene.polygons[0].getSize() << std::endl;
        // write every point
        for (int i=0; i<scene.polygons[0].getSize(); ++i) {
            Point p = scene.polygons[0].getPoint(i);
            fout << p.x << " " << p.y << std::endl;
        }
    } catch (std::exception& ex) {
        m_errorMessage = "File \"" + QString(filename) + "\" is corrupted or missing";
        return false;
    }

    return true;
}

QString FileProcessor::getError() const
{
    return m_errorMessage;
}
