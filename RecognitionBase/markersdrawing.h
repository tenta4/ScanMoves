#ifndef MARKERSDRAWING_H
#define MARKERSDRAWING_H
#include "opencv/highgui.h"
#include "MarkersStorage/markersstorage.h"
class MarkersDrawing
{
public:
    static void draw(IplImage*, const std::vector <Marker> markers, CvScalar color = cvScalar(128));
    static void draw(std::vector <IplImage*>, const MarkersStorage markers);
    static void draw(IplImage*, const MarkersStorage markers, int gradient = 1);
};

#endif // MARKERSDRAWING_H
