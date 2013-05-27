#ifndef MARKERFINDER_H
#define MARKERFINDER_H
#include "vector"
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "colorsstorage.h"
#include "../MarkersStorage/marker.h"
class MarkerFinder
{
private:
    enum FROM_WHERE_COME_IN { FROM_LEFT , FROM_RIGHT , FROM_TOP , FROM_BOTTOM , FROM_CENTER };
    enum FLAGS{FLAG_EMPTY = 255 , FLAG_FULL = 128};
    void recursion(int x, int y, uchar* ptr, FROM_WHERE_COME_IN);
    unsigned int image_width;
    unsigned int image_height;

    IplImage* tmp_graystyle_image;
    Marker m;
    void inRange(IplImage* src,std::vector <ColorsTrasholds> colors, IplImage* dst);
public:
    std::vector <Marker> getMarkers(IplImage* image, const ColorsStorage* colors_to_find);
    MarkerFinder(CvSize image_size);
    ~MarkerFinder();
};

#endif // MARKERFINDER_H
