#include "webcam.h"

WebCam::WebCam(const char* dist_coeff_path, const char * camera_matrix_path)
{
    capture = 0;
    capture = cvCaptureFromCAM(0 );
    if (!capture) throw std::out_of_range("open camera error");

    size.height = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    size.width = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);

    if (camera_matrix_path && dist_coeff_path)
    {
        mapx = 0;
        mapy = 0;

        dist_coef = (CvMat*)cvLoad(dist_coeff_path);
        camera_matrix = (CvMat*)cvLoad(camera_matrix_path);

        if (dist_coef && camera_matrix)
        {
            mapx = cvCreateImage( size, IPL_DEPTH_32F, 1 );
            mapy = cvCreateImage( size, IPL_DEPTH_32F, 1 );
            cvInitUndistortMap( camera_matrix, dist_coef, mapx, mapy );
        }
        else
        {
            std::cerr<<"\nCan't to find calibration files\n";
        }
    }

}
IplImage * WebCam::getFrame()
{
    if( !cvGrabFrame( capture ))
        throw std::out_of_range("frame grabbing error");
    IplImage* image1 = cvRetrieveFrame( capture );

    if (mapx)
    {
        IplImage *t = cvCloneImage( image1 );

        cvRemap( image1, t, mapx, mapy,CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, CV_RGB(255,0,0)); // undistort image
        cvFlip(t, image1, 1);
        cvReleaseImage( &t );
    }else cvFlip(image1, image1, 1);
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
