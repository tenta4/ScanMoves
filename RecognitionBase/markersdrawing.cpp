#include "markersdrawing.h"
#include "QDebug"
void MarkersDrawing::draw(IplImage * image, const std::vector<Marker> found_markers)
{
    qDebug()<<found_markers.size()<<"size";
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

void MarkersDrawing::draw(std::vector<IplImage *> images, const MarkersStorage markers)
{
    const std::vector <std::vector <Marker> >  all_video_markers = markers.getMarkersVector();
    if (images.size() != all_video_markers.size()) return;

    for (int i = 0 ; i < images.size() ; i++)
    {
        MarkersDrawing::draw(images.at(i), all_video_markers.at(i));
    }

}
