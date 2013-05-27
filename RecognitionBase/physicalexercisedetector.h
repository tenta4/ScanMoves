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
    PhysicalExerciseDetector(CvSize2D32f camera_angles, int images_width, int images_height, float marker_size);
    void pushBackGroungImage(const IplImage*);
    void pushEtalonMarkersImage(const IplImage*, std::vector <CvPoint> init_markers_position);
    void pushGameImage(const IplImage*);
    void saveMovement(const char * name);
    MarkersStorage   getMarkersStorage();
    void clearMarkersStorage();
    ~PhysicalExerciseDetector();

};

#endif // PHYSICALEXERCISEDETECTOR_H
