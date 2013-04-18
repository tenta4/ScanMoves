#ifndef PHYSICALEXERCISEDETECTOR_H
#define PHYSICALEXERCISEDETECTOR_H
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "BackgroundSubtraction/bgdetector.h"
#include "BackgroundSubtraction/bgteacher.h"

#include "MarkerFinder/markerfinder.h"
#include "MarkerFinder/colorsstorage.h"

class PhysicalExerciseDetector
{
    BGTeacher *bgteacher;
    BGDetector *bgdetector;
    MarkerFinder* marker_finder;
    ColorsStorage* colors_storage;
public:
    PhysicalExerciseDetector();
    void pushBackGroungImage(const IplImage*);
    void pushEtalonMarkersImage(const IplImage*, std::vector <CvPoint> init_markers_position);
    void pushGameImage(const IplImage*);
};

#endif // PHYSICALEXERCISEDETECTOR_H
