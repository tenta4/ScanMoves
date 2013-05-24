#ifndef MARKERSSTORAGE_H
#define MARKERSSTORAGE_H

#include "vector"
#include "../marker.h"
#include "opencv/highgui.h"

class MarkersStorage
{
    float focal_length;
    float markers_real_size;
    std::vector <std::vector <Marker> >        all_video_markers;

public:
    void pushMarkers(std::vector <Marker> input_markers);

    const std::vector <std::vector <Marker> >   getMarkers();

    MarkersStorage(float focal_length, float markers_real_size);
    ~MarkersStorage();
    //void saveMovement(const char* name);
};

#endif // MARKERSSTORAGE_H
