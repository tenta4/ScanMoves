#include "markersdrawing.h"

void MarkersDrawing::draw(IplImage * image, std::vector<Marker> found_markers)
{
    for (int i = 0 ; i < found_markers.size() ; i++)
    {
        Marker m = found_markers.at(i);
        cvDrawCircle(image,m.left,    5, cvScalar(128),2);
        cvDrawCircle(image,m.rihgt,   5, cvScalar(128),2);
        cvDrawCircle(image,m.top,     5, cvScalar(128),2);
        cvDrawCircle(image,m.buttom,  5, cvScalar(128),2);

        cvDrawLine  (image,m.left,    m.top,      cvScalar(128),2);
        cvDrawLine  (image,m.top,     m.rihgt,    cvScalar(128),2);
        cvDrawLine  (image,m.buttom,  m.rihgt,    cvScalar(128),2);
        cvDrawLine  (image,m.left,    m.buttom,   cvScalar(128),2);

    }

}
