#ifndef PHYSICALEXERCISEDETECTOR_H
#define PHYSICALEXERCISEDETECTOR_H
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "BackgroundSubtraction/bgdetector.h"
#include "BackgroundSubtraction/bgteacher.h"

#include "MarkerFinder/markerfinder.h"
#include "MarkerFinder/colorsstorage.h"

#include "MarkersStorage/markersstorage.h"
#include "markersdrawing.h"
class PhysicalExerciseDetector
{
    int images_width;
    int images_height;
    IplImage* hsv_tmp_img;
    BGTeacher* bgteacher;
    BGDetector* bgdetector;
    MarkerFinder* marker_finder;
    ColorsStorage* colors_storage;
    MarkersStorage* markers_storage;

public:
    PhysicalExerciseDetector(int images_width, int images_height);
    void pushBackGroungImage(const IplImage*);
    void pushEtalonMarkersImage(const IplImage*, std::vector <CvPoint> init_markers_position);
    void pushGameImage(const IplImage*);
    void saveMovement(const char * name);
    const std::vector <std::vector <Marker> >   getMarkers();
    ~PhysicalExerciseDetector();

};

#endif // PHYSICALEXERCISEDETECTOR_H
