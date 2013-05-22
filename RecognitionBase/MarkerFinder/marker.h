#ifndef MARKER_H
#define MARKER_H

#include "opencv/highgui.h"

struct Marker
{

    CvPoint left;
    CvPoint rihgt;
    CvPoint top;
    CvPoint buttom;
    int     acreage;
    int     id_marker;

    Marker();
    Marker (int id);

    float getMaxWidth();

};


#endif // MARKER_H
