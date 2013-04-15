#include "physicalexercisedetector.h"

PhysicalExerciseDetector::PhysicalExerciseDetector()
{
    bgdetector = new BGDetector(40);
}
void PhysicalExerciseDetector::pushBackGroungImage(const IplImage * input_img)
{
    IplImage * hsv = cvCreateImage(cvGetSize(input_img),8,3);
    cvCvtColor(input_img,hsv, CV_BGR2HSV);
    bgdetector->push(hsv);
}
void PhysicalExerciseDetector::pushEtalonMarkersImage(const IplImage * input_img, std::vector <CvPoint> init_markers_position)
{

    bgdetector->calc();

    IplImage * hsv = cvCreateImage(cvGetSize(input_img),8,3);
    cvCvtColor(input_img,hsv, CV_BGR2HSV);

    marker_finder.setEtalon(hsv,init_markers_position);
    cvReleaseImage(&hsv);
}

void PhysicalExerciseDetector::pushGameImage(const IplImage * input_img)
{
    IplImage * hsv = cvCreateImage(cvGetSize(input_img),8,3);
    cvCvtColor(input_img,hsv, CV_BGR2HSV);
    bgdetector->checkImg(hsv);
    marker_finder.getMarkers(hsv);
    cvReleaseImage(&hsv);
}
