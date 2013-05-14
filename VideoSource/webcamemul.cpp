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

    FILE * pFile;
    pFile = fopen ( count_frames_c , "rb" );

    if (pFile == NULL)
    {
        if ( count_frames_i == 0 )throw std::out_of_range("error grab frame");
        else count_frames_i =  0;
    }
    fread(image->imageData,image->width*image->height*image->nChannels,1, pFile);
    fclose(pFile);

    count_frames_i++;

    return image;
}
int WebCamEmul::getHeight()
{
    return 480;
}
int WebCamEmul::getWidth()
{
    return 640;
}
WebCamEmul::~WebCamEmul(){}
