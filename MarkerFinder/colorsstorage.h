#ifndef COLORSSTORAGE_H
#define COLORSSTORAGE_H

#include "vector"
#include "opencv/highgui.h"

class ColorsStorage
{
    std::vector <CvScalar> etalon_marker_colors;
public:
    ColorsStorage();
    void setEtalon(const IplImage*, std::vector <CvPoint> init_markers_position);
    std::vector <CvScalar> getColors() const;
};

#endif // COLORSSTORAGE_H
