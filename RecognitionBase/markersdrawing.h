#ifndef MARKERSDRAWING_H
#define MARKERSDRAWING_H
#include "opencv/highgui.h"
#include "MarkersStorage/markersstorage.h"
class MarkersDrawing
{
public:
    static void draw(IplImage*, std::vector <Marker> markers);
    static void draw(std::vector <IplImage*>, MarkersStorage markers);
};

#endif // MARKERSDRAWING_H
