#ifndef IWEBCAM_H
#define IWEBCAM_H
#include "opencv/highgui.h"
#include <stdexcept>

class IWebCam
{
protected:
    CvSize size;

public:
    IWebCam();
    virtual IplImage * getFrame() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    CvSize2D32f getCameraAngles();

    virtual ~IWebCam();
};

#endif // IWEBCAM_H
