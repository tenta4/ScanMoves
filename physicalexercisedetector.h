#ifndef PHYSICALEXERCISEDETECTOR_H
#define PHYSICALEXERCISEDETECTOR_H
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "BackgroundSubtraction/bgdetector.h"
#include "markerfinder.h"
class PhysicalExerciseDetector
{
    BGDetector *bgdetector;
    MarkerFinder marker_finder;
public:
    PhysicalExerciseDetector();
    void pushBackGroungImage(const IplImage*);
    void pushEtalonMarkersImage(const IplImage*, std::vector <CvPoint> init_markers_position);
    void pushGameImage(const IplImage*);
};

#endif // PHYSICALEXERCISEDETECTOR_H
