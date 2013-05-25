#ifndef MARKERSDRAWING_H
#define MARKERSDRAWING_H
#include "opencv/highgui.h"
#include "MarkersStorage/markersstorage.h"
class MarkersDrawing
{
public:
    static void draw(IplImage*, const std::vector <Marker> markers);
    static void draw(std::vector <IplImage*>, const MarkersStorage markers);
};

#endif // MARKERSDRAWING_H
