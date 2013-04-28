#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#define WRITE_TO_FILE 0
#define MAX_CAM_CADR 10
#include "opencv/highgui.h"
#include "vector"
#include "string"
#include "iostream"
#include "QDebug"

#include "VideoSource/webcamemul.h"
#include "VideoSource/webcam.h"

#include "physicalexercisedetector.h"
class GameModule
{

    int getMenueItem( std::vector <std::string> items);
    void adaptationMode();
    int gameMode();
    IWebCam *camera;
    PhysicalExerciseDetector* detector;
    int waitingWND(const char*, bool is_show_timer = true, int delay = 30);
public:
    GameModule();
    ~GameModule();
};

#endif // GAMEMODULE_H
