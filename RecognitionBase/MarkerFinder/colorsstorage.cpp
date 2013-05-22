#include "colorsstorage.h"

ColorsStorage::ColorsStorage(uint h_trashold, uint s_trashold, uint v_trashold):
    h_trashold(h_trashold), s_trashold(s_trashold), v_trashold(v_trashold)
{
}
void ColorsStorage::setEtalon(const IplImage *input_img, std::vector <CvPoint> init_markers_position)
{

    etalon_marker_colors.clear();
    for (int i = 0 ; i<init_markers_position.size() ; i++)
    {
        CvScalar color = cvGet2D(input_img,init_markers_position.at(i).y, init_markers_position.at(i).x);
        ColorsTrasholds trasholds;

        trasholds.h_bottom = color.val[0] - h_trashold;
        trasholds.s_bottom = color.val[1] - s_trashold;
        trasholds.v_bottom = color.val[2] - v_trashold;

        trasholds.h_top = color.val[0] + h_trashold;
        trasholds.s_top = color.val[1] + s_trashold;
        trasholds.v_top = color.val[2] + v_trashold;


        etalon_marker_colors.push_back(trasholds);
    }

}
std::vector <ColorsTrasholds> ColorsStorage::getColors() const
{
    return etalon_marker_colors;
}
