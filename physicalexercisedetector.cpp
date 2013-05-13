#include "physicalexercisedetector.h"

PhysicalExerciseDetector::PhysicalExerciseDetector(int w, int h)
{
    if (w<320 || w>2560 || h<240 && h<1536) throw std::out_of_range("bad images size");
    images_width   = w;
    images_height  = h;
    marker_finder  = 0;
    bgdetector     = 0;
    bgteacher      = new BGTeacher(w, h);
    colors_storage = new ColorsStorage();
    hsv_tmp_img    = cvCreateImage(cvSize(640,480),8,3);

}
void PhysicalExerciseDetector::pushBackGroungImage(const IplImage * input_img)
{
    cvCvtColor(input_img,hsv_tmp_img, CV_BGR2HSV);
    bgteacher->push(hsv_tmp_img);
}
void PhysicalExerciseDetector::pushEtalonMarkersImage(const IplImage * input_img, std::vector <CvPoint> init_markers_position)
{
    cvCvtColor(input_img,hsv_tmp_img, CV_BGR2HSV);
    colors_storage->setEtalon(hsv_tmp_img,init_markers_position);
}

void PhysicalExerciseDetector::pushGameImage(const IplImage * input_img)
{
    if (input_img->width != images_width || input_img->height != images_height)
        throw std::out_of_range("resolution error in PhysicalExerciseDetector");

    if (marker_finder && bgteacher->getMiddle())
    {
        cvCvtColor(input_img,hsv_tmp_img, CV_BGR2HSV);
        bgdetector->checkImg(hsv_tmp_img);
        std::vector <Marker> found_markers = marker_finder->getMarkers(hsv_tmp_img, colors_storage);
        all_video_markers.push_back(found_markers);

        for (int i = 0 ; i < found_markers.size() ; i++)
        {
            Marker m = found_markers.at(i);
            cvDrawCircle(hsv_tmp_img,m.left,    5, cvScalar(128),2);
            cvDrawCircle(hsv_tmp_img,m.rihgt,   5, cvScalar(128),2);
            cvDrawCircle(hsv_tmp_img,m.top,     5, cvScalar(128),2);
            cvDrawCircle(hsv_tmp_img,m.buttom,  5, cvScalar(128),2);

            cvDrawLine  (hsv_tmp_img,m.left,    m.top,      cvScalar(128),2);
            cvDrawLine  (hsv_tmp_img,m.top,     m.rihgt,    cvScalar(128),2);
            cvDrawLine  (hsv_tmp_img,m.buttom,  m.rihgt,    cvScalar(128),2);
            cvDrawLine  (hsv_tmp_img,m.left,    m.buttom,   cvScalar(128),2);

            std::cerr<<"dist"<<m.dist<<"\n";

        }
        cvShowImage("ScanMoves", hsv_tmp_img);
    }
    else
    {
        bgteacher->calc();
        delete bgdetector;
        bgdetector = new BGDetector(bgteacher, 40, 8);
        marker_finder = new MarkerFinder(cvSize(images_width, images_height));
    }
}
PhysicalExerciseDetector::~PhysicalExerciseDetector()
{
    delete colors_storage;
    delete marker_finder;
    delete bgdetector;
    delete bgteacher;
    cvReleaseImage(&hsv_tmp_img);
}
