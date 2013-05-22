#ifndef MARKERSSTORAGE_H
#define MARKERSSTORAGE_H

#include "vector"
#include "../MarkerFinder/marker.h"
#include "opencv/highgui.h"
#include "markerpolarcs.h"
class MarkersStorage
{
    float focal_length;
    float markers_real_size;
    std::vector <std::vector <Marker> >        all_video_markers;
    std::vector <std::vector <MarkerPolarCS> > polar_markers;
    std::vector <IplImage*> images;
public:
    void pushMarkers(std::vector <Marker> input_markers);
    void pushImage  (IplImage* input_images );
    MarkersStorage(float focal_length, float markers_real_size);
    ~MarkersStorage();
    void saveMovement(const char* name);
};

#endif // MARKERSSTORAGE_H
