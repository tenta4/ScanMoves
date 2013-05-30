#include "physicalexercisedetector.h"

PhysicalExerciseDetector::PhysicalExerciseDetector(CvSize2D32f camera_angles, int width, int height, float marker_size)
{
    if (width<320 || width>2560 || height<240 && height<1536) throw std::out_of_range("bad images size");
    images_width   = width;
    images_height  = height;
    marker_finder  = 0;
    bgdetector     = 0;
    bgteacher      = new BGTeacher(width, height);
    colors_storage = new ColorsStorage(20, 60, 60);
    markers_storage= new MarkersStorage(camera_angles, cvSize2D32f(images_width, images_height), marker_size);

    hsv_tmp_img    = cvCreateImage(cvSize(640,480),8,3);

}
void PhysicalExerciseDetector::clearMarkersStorage()
{
    markers_storage->clearStorage();
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

std::vector <Marker> PhysicalExerciseDetector::pushGameImage(const IplImage * input_img)
{
    if (input_img->width != images_width || input_img->height != images_height)
        throw std::out_of_range("resolution error in PhysicalExerciseDetector");

    if (!marker_finder || !bgteacher->getMiddle())
    {
        bgteacher->calc();
        delete bgdetector;
        bgdetector = new BGDetector(bgteacher, 40, 8);
        marker_finder = new MarkerFinder(cvSize(images_width, images_height));
    }

    {
        cvCvtColor(input_img,hsv_tmp_img, CV_BGR2HSV);
        bgdetector->checkImg(hsv_tmp_img);
        std::vector <Marker> found_markers = marker_finder->getMarkers(hsv_tmp_img, colors_storage);
        found_markers = markers_storage->pushImageMarkers(found_markers);
        return found_markers;
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

MarkersStorage  PhysicalExerciseDetector::getMarkersStorage()
{
    return *markers_storage;
}

void PhysicalExerciseDetector::saveMovement(const char *name)
{

}
