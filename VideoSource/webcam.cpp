#include "webcam.h"

WebCam::WebCam()
{
    capture = 0;
    capture = cvCaptureFromCAM(0 );
    if (!capture) throw ErrorOpenCamera();

    size.height = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    size.width = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);


}
IplImage * WebCam::getFrame()
{
    if( !cvGrabFrame( capture ))
        throw ErrorGrabFrame();
    IplImage* image1 = cvRetrieveFrame( capture );
    return image1;
}
int WebCam::getHeight()
{
    return size.height;
}
int WebCam::getWidth()
{
    return size.width;
}
WebCam::~WebCam()
{
    cvReleaseCapture( &capture );
}
