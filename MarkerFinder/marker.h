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

    int getMaxWidth()
    {
        int screen_size1 = sqrt ((left.x-rihgt.x)*(left.x-rihgt.x)+(left.y-rihgt.y)*(left.y-rihgt.y));
        int screen_size2 = sqrt ((top.x-buttom.x)*(top.x-buttom.x)+(top.y-buttom.y)*(top.y-buttom.y));
        return ( screen_size1>screen_size2 ? screen_size1 : screen_size2);

    }
};


#endif // MARKER_H
