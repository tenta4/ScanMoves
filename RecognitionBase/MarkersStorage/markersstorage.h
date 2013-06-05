#ifndef MARKERSSTORAGE_H
#define MARKERSSTORAGE_H

#include "vector"
#include "marker.h"
#include "opencv/highgui.h"

class MarkersStorage
{
    float markers_real_size;
    CvSize2D32f camera_angles;
    CvSize2D32f image_resol;
    CvSize2D32f half_camera_ang;
    CvSize2D32f half_image_size;
    std::vector <std::vector <Marker> >        all_video_markers;

public:
    std::vector <Marker> pushImageMarkers(std::vector <Marker> input_markers);
    void pushPolarMarkers(std::vector <Marker> input_markers);
    std::vector <std::vector <Marker> >   getMarkersVector() const {return all_video_markers;}
    //std::vector <std::vector <Marker> >&  getMarkersVector() {return all_video_markers;}
    void convertToImageCS();
    void clearStorage();
    MarkersStorage(
            CvSize2D32f camera_angles,
            CvSize2D32f image_resol,
            float markers_real_size = 80);
    ~MarkersStorage();
};

#endif // MARKERSSTORAGE_H
