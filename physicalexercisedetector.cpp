#include "physicalexercisedetector.h"

PhysicalExerciseDetector::PhysicalExerciseDetector()
{
    marker_finder = 0;
    bgdetector = 0;
    bgteacher = new BGTeacher();
    colors_storage = new ColorsStorage();
    hsv_tmp_img = cvCreateImage(cvSize(640,480),8,3);

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
    if (marker_finder)
    {
        cvCvtColor(input_img,hsv_tmp_img, CV_BGR2HSV);
        bgdetector->checkImg(hsv_tmp_img);
        marker_finder->getMarkers(hsv_tmp_img, colors_storage);
    }
    else
    {
        bgteacher->calc();
        delete bgdetector;
        bgdetector = new BGDetector(bgteacher, 40, 4);
        marker_finder = new MarkerFinder();
    }
}
PhysicalExerciseDetector::~PhysicalExerciseDetector()
{
    cvReleaseImage(&hsv_tmp_img);
}
