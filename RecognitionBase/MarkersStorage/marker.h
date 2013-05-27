#ifndef MARKER_H
#define MARKER_H

#include "opencv/highgui.h"

struct Marker
{
    int     id_marker;

    CvPoint left;
    CvPoint rihgt;
    CvPoint top;
    CvPoint buttom;
    int     acreage;

    float   angle_x;
    float   angle_y;
    float   coord_z;

    Marker();
    Marker (int id);

    float getMaxWidth();

};


#endif // MARKER_H
