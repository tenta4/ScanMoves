#ifndef WEBCAM_H
#define WEBCAM_H
#include "iwebcam.h"
#include "opencv/highgui.h"
#include "opencv/cv.h"
class WebCam :public IWebCam
{
private:
    CvCapture* capture;
public:
    WebCam();
    IplImage * getFrame();
    int getWidth();
    int getHeight();

    ~WebCam();
};

#endif // WEBCAM_H
