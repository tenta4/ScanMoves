#include <QtGui/QApplication>
#include "mainwindow.h"

#include <opencv2/video/background_segm.hpp>
#include <opencv2/legacy/legacy.hpp>

#define MAX_CAM_CADR 10
#include "QDebug"
#include "webcam.h"
#include "iwebcam.h"
#include "webcamemul.h"

#include "physicalexercisedetector.h"
#define WRITE_TO_FILE 0//1-write 2-read
void writeToFile(const IplImage* image)
{
    static int count_frames_i = 0;
    static char count_frames_c[9];

    if (count_frames_i == 0)
    {
        while(1)
        {
            sprintf(count_frames_c,"%d.bin",count_frames_i);
            count_frames_i++;
            int i;
            if( i=remove( count_frames_c ) != 0 )
                break;
        }
        count_frames_i = 0;
    }

    sprintf(count_frames_c,"%d.bin",count_frames_i);
    count_frames_i++;
    FILE * pFile;
    pFile = fopen ( count_frames_c , "wb" );
    fwrite(image->imageData,1,image->width*image->height*image->nChannels, pFile);
    fclose(pFile);
}

int main(int argc, char** argv)
{

          // сздаем окно
          cvNamedWindow( "Motion", 1 );

          IWebCam *camera;

          if (WRITE_TO_FILE != 2)  camera = new WebCam();
          else camera = new WebCamEmul();

          PhysicalExerciseDetector detector;


          /**************************
          * Message to user
          ***************************/

          if (WRITE_TO_FILE == 0)   for(;;)
          {
                    IplImage* image = camera->getFrame();
                    CvFont font;
                    cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 1.3f, 1.3f,0,3, 8 );
                    cvPutText( image, "Get away and press any key", cvPoint(4,120), &font, CV_RGB(0,0,255) );

                    cvShowImage( "Motion", image);
                    if( cvWaitKey(10) >= 0 )  break;
                    //cvReleaseImage(&image1);
          }


          /**************************
          * Remember background color
          ***************************/

          for(int i=0;i<MAX_CAM_CADR;i++)
          {

                IplImage* image = camera->getFrame();
                if (i<MAX_CAM_CADR/2) continue;
                detector.pushBackGroungImage(image);

                if (WRITE_TO_FILE == 1) writeToFile(image);

                cvShowImage( "Motion", image);

                //cvReleaseImage(&image);

                cvWaitKey(20);

          }

          /**************************
          * Getting markers colors
          ***************************/

          for(int i=0;i<MAX_CAM_CADR*4;i++)
          {

                IplImage* image = camera->getFrame();

                if (WRITE_TO_FILE == 1)
                {
                    writeToFile(image);
                }

                std::vector <CvPoint> init_positions;
                init_positions.push_back(cvPoint(image->width/2,image->height/2));
                //init_positions.push_back(cvPoint(image->width/3-50,image->height/2));

                detector.pushEtalonMarkersImage(image, init_positions);

                CvFont font;
                cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 1.3f, 1.3f,0,3, 8 );

                cvPutText( image, "Show me the marker here",  cvPoint(70,120), &font, CV_RGB(0,0,255)  );
                for (int i = 0 ; i<init_positions.size() ; i++)
                    cvDrawCircle(image,init_positions.at(i),10,cvScalar(200,200,0),3);

                cvWaitKey(20);

                cvShowImage( "Motion", image);

                //cvReleaseImage(&image);

          }


          /**************************
          * Scaning images
          ***************************/

          for(;;)
          {
                IplImage* image = 0;

                try
                {
                    image = camera->getFrame();
                }
                catch(IWebCam::ErrorGrabFrame e){break;}

                if (WRITE_TO_FILE == 1)
                {
                    writeToFile(image);
                }
                cvShowImage("Motion",image);
                detector.pushGameImage(image);

                if( cvWaitKey(1) >= 0 ) break;

                //cvReleaseImage(&image);
          }

          //Удаляем все
          delete camera;
          cvDestroyWindow( "Motion" );

    return 0;
}

