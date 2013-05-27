#include "iwebcam.h"

IWebCam::IWebCam()
{
}
IWebCam::~IWebCam(){}
CvSize2D32f IWebCam::getCameraAngles()
{
    return cvSize2D32f(60,44);
}
