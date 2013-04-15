#ifndef WEBCAMEMUL_H
#define WEBCAMEMUL_H
#include "iwebcam.h"
#include "stdio.h"
class WebCamEmul : public IWebCam
{
    int count_frames_i;
    char count_frames_c[9];

public:
    WebCamEmul();
    IplImage * getFrame();
    int getWidth();
    int getHeight();

    ~WebCamEmul();

};

#endif // WEBCAMEMUL_H
