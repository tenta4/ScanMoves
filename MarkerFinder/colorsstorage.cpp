#include "colorsstorage.h"

ColorsStorage::ColorsStorage()
{
}
void ColorsStorage::setEtalon(const IplImage *input_img, std::vector <CvPoint> init_markers_position)
{

    etalon_marker_colors.clear();
    for (int i = 0 ; i<init_markers_position.size() ; i++)
    {
        etalon_marker_colors.push_back(
              cvGet2D(input_img,init_markers_position.at(i).y, init_markers_position.at(i).x));
    }

}
std::vector <CvScalar> ColorsStorage::getColors() const
{
    return etalon_marker_colors;
}
