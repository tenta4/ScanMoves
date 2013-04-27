#ifndef WEBCAM_H
#define WEBCAM_H
#include "iwebcam.h"
#include "opencv/highgui.h"
#include "opencv/cv.h"
class WebCam :public IWebCam
{
private:
    CvCapture* capture;
    CvMat *camera_matrix;
    CvMat *dist_coef;
    IplImage* mapx;
    IplImage* mapy;
public:
    WebCam(const char* dist_coeff = 0, const char * camera_matrix = 0);
    IplImage * getFrame();
    int getWidth();
    int getHeight();

    ~WebCam();
};

#endif // WEBCAM_H
