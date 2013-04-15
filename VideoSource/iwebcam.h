#ifndef IWEBCAM_H
#define IWEBCAM_H
#include "opencv/highgui.h"
class IWebCam
{
protected:
    CvSize size;

public:
    class ErrorOpenCamera{};
    class ErrorGrabFrame{};
    IWebCam();
    virtual IplImage * getFrame() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual ~IWebCam();
};

#endif // IWEBCAM_H
