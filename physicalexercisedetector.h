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
    int images_width;
    int images_height;
    IplImage* hsv_tmp_img;
    BGTeacher *bgteacher;
    BGDetector *bgdetector;
    MarkerFinder* marker_finder;
    ColorsStorage* colors_storage;

    std::vector <std::vector <Marker> > all_video_markers;
public:
    PhysicalExerciseDetector(int images_width, int images_height);
    void pushBackGroungImage(const IplImage*);
    void pushEtalonMarkersImage(const IplImage*, std::vector <CvPoint> init_markers_position);
    void pushGameImage(const IplImage*);
    ~PhysicalExerciseDetector();
};

#endif // PHYSICALEXERCISEDETECTOR_H
