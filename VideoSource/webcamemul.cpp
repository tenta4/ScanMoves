#include "webcamemul.h"
#include "QDebug"
WebCamEmul::WebCamEmul()
{
    count_frames_i = 0;

}
IplImage * WebCamEmul::getFrame()
{
    IplImage * image = cvCreateImage(cvSize(640,480),8,3);
    sprintf(count_frames_c,"%d.bin",count_frames_i);
    count_frames_i++;
    FILE * pFile;
    pFile = fopen ( count_frames_c , "rb" );
    if (pFile == NULL) throw ErrorGrabFrame();
    fread(image->imageData,image->width*image->height*image->nChannels,1, pFile);
    fclose(pFile);
    return image;
}
int WebCamEmul::getHeight()
{

}
int WebCamEmul::getWidth()
{

}
WebCamEmul::~WebCamEmul(){}
