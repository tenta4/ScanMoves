#ifndef MARKERSDRAWING_H
#define MARKERSDRAWING_H
#include "opencv/highgui.h"
#include "marker.h"
class MarkersDrawing
{
public:
    static void draw(IplImage*, std::vector <Marker> markers);
    static void draw(std::vector <IplImage*>, std::vector <std::vector <Marker> > markers);
};

#endif // MARKERSDRAWING_H
