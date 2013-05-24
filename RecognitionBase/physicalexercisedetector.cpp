#include "physicalexercisedetector.h"

PhysicalExerciseDetector::PhysicalExerciseDetector(int w, int h)
{
    if (w<320 || w>2560 || h<240 && h<1536) throw std::out_of_range("bad images size");
    images_width   = w;
    images_height  = h;
    marker_finder  = 0;
    bgdetector     = 0;
    bgteacher      = new BGTeacher(w, h);
    colors_storage = new ColorsStorage(20, 60, 60);
    markers_storage= new MarkersStorage(710, 80);

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
        markers_storage->pushMarkers(found_markers);

        MarkersDrawing::draw(hsv_tmp_img, found_markers);

        cvShowImage("ScanMoves", hsv_tmp_img);
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
    markers_storage->convertToPolarCS();
    return *markers_storage;
}

void PhysicalExerciseDetector::saveMovement(const char *name)
{

}
