#include "gamemodule.h"

void _writeToFile(const IplImage* image)
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


GameModule::GameModule()
{
    if (WRITE_TO_FILE != 2)  camera = new WebCam("../distorsion_coeff.xml","../camera_matrix.xml");
    else camera = new WebCamEmul();

    detector = new PhysicalExerciseDetector(camera->getCameraAngles(),camera->getWidth(),camera->getHeight(), MARKERS_SIZE);

    cvNamedWindow("ScanMoves", CV_WINDOW_NORMAL);
    cvSetWindowProperty("ScanMoves", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    std::vector <std::string> items;
    items.push_back("PLAY");
    items.push_back("ADAPTATE");
    items.push_back("EXIT");

    adaptationMode();

    while (1)
    {
        int selected = getMenueItem(items);
        switch (selected)
        {
            case 0:
            {
                gameMode();
                break;
            }
            case 1:
            {
                adaptationMode();
                break;
            }
            case 2:
            {
                return;
            }
        }
    }
}
void GameModule::showTaskMode(char *movement_name)
{
    std::vector <IplImage*> images;
    MarkersIO::openMovement(movement_name, images);
    for (int i = 0 ; 1 ; i++)
    {
        cvShowImage("ScanMoves", images.at(i%images.size()));
        char c = cvWaitKey(30);
        if (c >= 0) break;
    }
}

int GameModule::gameMode()
{

    char* movement_name = "two_markers";

    //showTaskMode(movement_name);

    MarkersStorage etal_ms(camera->getCameraAngles(), cvSize2D32f(camera->getWidth(),camera->getHeight()));
    MarkersIO::openMovement(movement_name, etal_ms);
    MarkersComparator comparator(etal_ms);
    std::vector <Marker> tmp_user;
    std::vector <Marker> tmp_etalon;

    QTime time;

    int sum = 0;
    int count = 0;
    for(;;)
    {
          time.start();

          IplImage* image = camera->getFrame();

          if (WRITE_TO_FILE == 1)
          {
              _writeToFile(image);
          }

          tmp_user = detector->pushGameImage(image);

          int result_id;
          comparator.compare(tmp_user, tmp_etalon, result_id);
          MarkersDrawing::draw(image, tmp_user, cvScalar(0, 0, 200));
          MarkersDrawing::draw(image, tmp_etalon, cvScalar(0, 200, 0));

          cvShowImage("ScanMoves", image);

          if( cvWaitKey(1) >= 0 ) break;
          if(result_id == -1) break;

          int timer_value = time.elapsed();
          sum += timer_value;
          count ++ ;
          qDebug()<<timer_value<<"time";
          qDebug()<<"middle"<<sum/count;

    }

    resultMode(movement_name);
    detector->clearMarkersStorage();

}

void GameModule::resultMode(char *movement_name)
{

    MarkersStorage user_ms = detector->getMarkersStorage();
    MarkersStorage etal_ms(camera->getCameraAngles(), cvSize2D32f(camera->getWidth(),camera->getHeight()));

    MarkersIO::openMovement(movement_name, etal_ms);

    std::vector <int> corresponds_indexes;
    qDebug()<<"result"<<MarkersComparator::compare(etal_ms, user_ms, corresponds_indexes);


    std::vector<std::vector <Marker> > ms = user_ms.getMarkersVector();
    std::vector<std::vector <Marker> > es = etal_ms.getMarkersVector();

    IplImage * all_mark = cvCreateImage(cvSize(640,480),8,3);
    IplImage* img_result = cvCreateImage(cvSize(640,480), 8, 3);
    MarkersDrawing::draw(all_mark, user_ms, 1);
    MarkersDrawing::draw(all_mark, etal_ms, 2);

    int position = 0;

    while (1)
    {
        if (position < 0) position = 0 ;
        else if (position >= ms.size()) position = ms.size()-1;
        cvCopy(all_mark, img_result);
        MarkersDrawing::draw(img_result, ms.at(position) , cvScalar(0, 0, 200));
        MarkersDrawing::draw(img_result, es.at(corresponds_indexes.at(position)), cvScalar(200, 0, 0));
        cvShowImage("ScanMoves", img_result);
        char c =cvWaitKey(10);
        if (c == 'a') position--;
        else if (c == 'd') position++;
        else if (c == 27) break;
    }
    cvReleaseImage(&img_result);
    cvReleaseImage(&all_mark);


}

void GameModule::adaptationMode()
{
    waitingWND("Go to screen");

    for(int i=0;i<MAX_CAM_CADR*6;i++)
    {

          IplImage* image = camera->getFrame();

          if (WRITE_TO_FILE == 1)
          {
              _writeToFile(image);
          }

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
    waitingWND("Go away from screen");
    for(int i=0;i<MAX_CAM_CADR;i++)
    {

          IplImage* image = camera->getFrame();
          if ( i < MAX_CAM_CADR/2) continue;
          detector->pushBackGroungImage(image);

          if (WRITE_TO_FILE == 1) _writeToFile(image);

          cvShowImage( "ScanMoves", image);

          cvWaitKey(20);

    }

    waitingWND("Adaptation finished", false);

}

int GameModule::waitingWND(const char* _text, bool is_timer, int delay)
{
    char text [100];

    for (int i = delay; i > 0 ; i--)
    {
        sprintf(text," %d" , i/10);
        IplImage* image = camera->getFrame();

        if (WRITE_TO_FILE == 1)
        {
            _writeToFile(image);
        }

        CvFont font;
        cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 1.3f, 1.3f,0,3, 8 );
        if (is_timer) cvPutText( image, text, cvPoint(4,50+120), &font, CV_RGB(0,255, 250) );
        cvPutText( image, _text, cvPoint(4,150+120), &font, CV_RGB(0,255, 250) );
        cvShowImage("ScanMoves",image);
        cvWaitKey(1);

    }
}

int GameModule::getMenueItem(std::vector <std::string> items)
{
    int selected = 0 ;
    while (1)
    {
        IplImage* image = cvCreateImage(cvSize(640, 480),8,3);
        for (int i = 0 ; i < items.size() ; i++)
        {
            CvFont font;
            cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 1.3f, 1.3f,0,3, 8 );
            cvPutText( image, items.at(i).c_str(), cvPoint(4,i*50+120), &font, CV_RGB(0,255, 250*(i == selected) ) );
            cvShowImage("ScanMoves", image);
        }
        char c = cvWaitKey(30);
        if (c == 'w' || c == 'ö') selected -- ;
        else if (c == 's' || c == 'û') selected ++ ;
        else if (c == 13 ) return selected;

        if (selected < 0) selected = items.size()-1;
        else if (selected > items.size()) selected = 0;

        selected %= items.size();
        cvReleaseImage(&image);
    }
}

GameModule::~GameModule()
{
    delete detector;
    delete camera;
}
