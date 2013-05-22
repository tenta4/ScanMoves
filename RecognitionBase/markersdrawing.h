#ifndef MARKERSDRAWING_H
#define MARKERSDRAWING_H
#include "opencv/highgui.h"
#include "MarkerFinder/marker.h"
class MarkersDrawing
{
public:
    static void draw(IplImage*, std::vector <Marker> markers);
};

#endif // MARKERSDRAWING_H
