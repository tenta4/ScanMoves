#include "webcamemul.h"
#include "QDebug"
WebCamEmul::WebCamEmul()
{
    count_frames_i = 0;
    tmp_image = cvCreateImage(cvSize(640,480),8,3);

}

IplImage * WebCamEmul::getFrame()
{
    sprintf(count_frames_c,"%d.bin",count_frames_i);

    FILE * pFile;
    pFile = fopen ( count_frames_c , "rb" );

    if (pFile == NULL)
    {
        if ( count_frames_i )
        {
            count_frames_i =  230;
            return getFrame();
        }
        else throw std::out_of_range("error grab frame");
    }

    fread(tmp_image->imageData,tmp_image->width*tmp_image->height*tmp_image->nChannels,1, pFile);
    fclose(pFile);

    count_frames_i++;

    return tmp_image;
}
int WebCamEmul::getHeight()
{
    return 480;
}
int WebCamEmul::getWidth()
{
    return 640;
}
WebCamEmul::~WebCamEmul()
{
    cvReleaseImage(&tmp_image);
}
