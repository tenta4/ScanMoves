#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#define MARKERS_SIZE 80
#define WRITE_TO_FILE 2
#define MAX_CAM_CADR 10
#include "opencv/highgui.h"
#include "vector"
#include "string"
#include "iostream"
#include "QDebug"

#include "VideoSource/webcamemul.h"
#include "VideoSource/webcam.h"

#include "RecognitionBase/physicalexercisedetector.h"
#include "RecognitionBase/markersio.h"
#include "RecognitionBase/markerscomparator.h"

#include "QTime"

class GameModule
{

    int getMenueItem( std::vector <std::string> items);
    void adaptationMode();
    void resultMode(char* movement_name);
    void showTaskMode(char* movement_name);
    int  gameMode();
    IWebCam *camera;
    MarkersSetRecognizer* detector;
    int waitingWND(const char*, bool is_show_timer = true, int delay = 60);
public:
    GameModule();
    ~GameModule();
};

#endif // GAMEMODULE_H
