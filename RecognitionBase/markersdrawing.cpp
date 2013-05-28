#include "markersdrawing.h"
#include "QDebug"
void MarkersDrawing::draw(IplImage * image, const std::vector<Marker> found_markers, CvScalar color)
{
    for (int i = 0 ; i < found_markers.size() ; i++)
    {
        Marker m = found_markers.at(i);
        cvDrawCircle(image,m.left,    5, color,2);
        cvDrawCircle(image,m.rihgt,   5, color,2);
        cvDrawCircle(image,m.top,     5, color,2);
        cvDrawCircle(image,m.buttom,  5, color,2);

        cvDrawLine  (image,m.left,    m.top,      color,2);
        cvDrawLine  (image,m.top,     m.rihgt,    color,2);
        cvDrawLine  (image,m.buttom,  m.rihgt,    color,2);
        cvDrawLine  (image,m.left,    m.buttom,   color,2);

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

void MarkersDrawing::draw(IplImage * image, const MarkersStorage markers, int gradient)
{
    std::vector <std::vector<Marker> > user_vec_vec = markers.getMarkersVector();
    for (int i = 0 ; i < user_vec_vec.size() ; i++)
    {
        std::vector <Marker> user_vec = user_vec_vec.at(i);
        for  (int j = 0 ; j < user_vec.size() ; j++)
        {
            CvScalar color;
            if (gradient == 1) color =  cvScalar((i*10)%120+120,(i*5)%120+120);
            else if (gradient == 2) color =  cvScalar(0,(i*5)%120+120, (i*10)%120+120);
            else color = cvScalar( gradient );
            MarkersDrawing::draw(image, user_vec, color);
        }
    }

}
