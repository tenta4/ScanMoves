#ifndef MARKERFINDER_H
#define MARKERFINDER_H
#include "vector"
#include "opencv/highgui.h"
#include "opencv/cv.h"
struct Marker
{
    const static int real_size = 800;
    const static double focal_l = 710;
    int dist;
    int index_in_colors_array;
    CvPoint left;
    CvPoint rihgt;
    CvPoint top;
    CvPoint buttom;
    int size;
    int id_marker;
    Marker(){}
    Marker (int id):id_marker(id)
    {
        size=0;
        left=cvPoint(10000,0);
        rihgt=cvPoint(0,0);
        top=cvPoint(0,10000);
        buttom=cvPoint(0,0);
    }
    int calcDistance()
    {
        int screen_size1 = sqrt ((left.x-rihgt.x)*(left.x-rihgt.x)+(left.y-rihgt.y)*(left.y-rihgt.y));
        int screen_size2 = sqrt ((top.x-buttom.x)*(top.x-buttom.x)+(top.y-buttom.y)*(top.y-buttom.y));
        int screen_size = ( screen_size1>screen_size2 ? screen_size1 : screen_size2);

        dist = focal_l * real_size / screen_size ;
        return dist;

    }
};
class MarkerFinder
{
private:
    enum FLAGS{FLAG_EMPTY = 255 , FLAG_FULL = 128};
    void recursion(int x, int y, uchar* ptr);
    unsigned int image_width;
    unsigned int image_height;

    std::vector <CvScalar> etalon_marker_colors;
    Marker m;
    void inRange(IplImage* src,std::vector <CvScalar> colors, int range, IplImage* dst);
public:
    void setEtalon(const IplImage*, std::vector <CvPoint> init_markers_position);
    std::vector <Marker> getMarkers(IplImage*);
};

#endif // MARKERFINDER_H
