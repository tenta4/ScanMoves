#ifndef MOVECREATOR_H
#define MOVECREATOR_H
#include "opencv/highgui.h"
#include "VideoSource/webcam.h"
#include "VideoSource/webcamemul.h"
#include "RecognitionBase/physicalexercisedetector.h"

#define USE_EMUL 1
#define MAX_CAM_CADR 10
#include "list"
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
    int waitingWND(const char*, bool is_show_timer = true, int delay = 60);

};

#endif // MOVECREATOR_H
