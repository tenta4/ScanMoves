#include "physicalexercisedetector.h"

PhysicalExerciseDetector::PhysicalExerciseDetector()
{
    marker_finder = 0;
    bgdetector = 0;
    bgteacher = new BGTeacher();
    colors_storage = new ColorsStorage();
}
void PhysicalExerciseDetector::pushBackGroungImage(const IplImage * input_img)
{
    IplImage * hsv = cvCreateImage(cvGetSize(input_img),8,3);
    cvCvtColor(input_img,hsv, CV_BGR2HSV);
    bgteacher->push(hsv);
}
void PhysicalExerciseDetector::pushEtalonMarkersImage(const IplImage * input_img, std::vector <CvPoint> init_markers_position)
{
    IplImage * hsv = cvCreateImage(cvGetSize(input_img),8,3);
    cvCvtColor(input_img,hsv, CV_BGR2HSV);

    colors_storage->setEtalon(hsv,init_markers_position);
    cvReleaseImage(&hsv);
}

void PhysicalExerciseDetector::pushGameImage(const IplImage * input_img)
{
    if (marker_finder)
    {

        IplImage * hsv = cvCreateImage(cvGetSize(input_img),8,3);
        cvCvtColor(input_img,hsv, CV_BGR2HSV);
        bgdetector->checkImg(hsv);
        marker_finder->getMarkers(hsv, colors_storage);
        cvReleaseImage(&hsv);
    }
    else
    {
        bgteacher->calc();
        delete bgdetector;
        bgdetector = new BGDetector(bgteacher, 40, 4);
        marker_finder = new MarkerFinder();
    }
}
