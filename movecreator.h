#ifndef MOVECREATOR_H
#define MOVECREATOR_H
#include "opencv/highgui.h"
#include "VideoSource/webcam.h"
#include "VideoSource/webcamemul.h"
#include "RecognitionBase/physicalexercisedetector.h"
#include "RecognitionBase/markersio.h"

#include "list"

#define USE_EMUL 0
#define MAX_CAM_CADR 10
#define MARKERS_SIZE 80

class MoveCreator
{
    IWebCam *camera;
    PhysicalExerciseDetector* detector;
    std::vector <IplImage*> images;
public:
    MoveCreator(const char* name);
    void adaptationMode();
    void recordMode();
    void visualMode();
    void saveMode(const char* name);
    int waitingWND(const char*, bool is_show_timer = true, int delay = 60);

};

#endif // MOVECREATOR_H
