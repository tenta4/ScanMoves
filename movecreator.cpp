#include "movecreator.h"
#include "Qdebug"

MoveCreator::MoveCreator(const char* name)
{
    if (!USE_EMUL)  camera = new WebCam("../distorsion_coeff.xml","../camera_matrix.xml");
    else camera = new WebCamEmul();

    detector = new PhysicalExerciseDetector(camera->getWidth(),camera->getHeight());
    adaptationMode();
    recordMode();
    visualMode();
    saveMode(name);
}

void MoveCreator::saveMode(const char *name)
{
    MarkersIO::saveMovement(name, detector->getMarkers(), images);
}

void MoveCreator::recordMode()
{
    for(;;)
    {
          IplImage* image = camera->getFrame();

          detector->pushGameImage(image);

          IplImage * tmp_image = cvCreateImage(cvGetSize(image),image->depth, image->nChannels);
          cvCopy(image, tmp_image);
          images.push_back(tmp_image);
          if (images.size() > 500) break;
          if( cvWaitKey(1) >= 0 ) break;

    }

}

int MoveCreator::waitingWND(const char* _text, bool is_timer, int delay)
{
    char text [100];

    for (int i = delay; i > 0 ; i--)
    {
        sprintf(text," %d" , i/10);
        IplImage* image = camera->getFrame();

        CvFont font;
        cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 1.3f, 1.3f,0,3, 8 );
        if (is_timer) cvPutText( image, text, cvPoint(4,50+120), &font, CV_RGB(0,255, 250) );
        cvPutText( image, _text, cvPoint(4,150+120), &font, CV_RGB(0,255, 250) );
        cvShowImage("ScanMoves",image);
        cvWaitKey(1);

    }
}

void MoveCreator::adaptationMode()
{
    waitingWND("Go away from screen");
    for(int i=0;i<MAX_CAM_CADR;i++)
    {

          IplImage* image = camera->getFrame();
          if ( i < MAX_CAM_CADR/2) continue;
          detector->pushBackGroungImage(image);

          cvShowImage( "ScanMoves", image);

          cvWaitKey(20);

    }
    waitingWND("Go to screen");

    for(int i=0;i<MAX_CAM_CADR*6;i++)
    {

          IplImage* image = camera->getFrame();

          std::vector <CvPoint> init_positions;
          init_positions.push_back(cvPoint(image->width/2,image->height/2));
          init_positions.push_back(cvPoint(image->width/3-50,image->height/2));

          detector->pushEtalonMarkersImage(image, init_positions);

          CvFont font;
          cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 1.3f, 1.3f,0,3, 8 );

          cvPutText( image, "Show me the marker here",  cvPoint(70,120), &font, CV_RGB(0,0,255)  );
          for (int i = 0 ; i<init_positions.size() ; i++)
              cvDrawCircle(image,init_positions.at(i),10,cvScalar(200,200,0),3);

          cvWaitKey(20);

          cvShowImage( "ScanMoves", image);

    }
    waitingWND("Begin your movement", true);


}

void MoveCreator::visualMode()
{
    std::vector <std::vector <Marker> > markers = detector->getMarkers();

    MarkersDrawing::draw(images, markers);

    int position = 0;

    while (1)
    {
        if (position < 0) position = 0 ;
        else if (position >= images.size()) position = images.size()-1;

        cvShowImage("ScanMoves", images[position]);
        char c =cvWaitKey(10);
        if (c == 'a') position--;
        else if (c == 'd') position++;
        else if (c == 27) return;
    }
}
