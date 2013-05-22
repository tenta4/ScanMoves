#ifndef COLORSSTORAGE_H
#define COLORSSTORAGE_H

#include "vector"
#include "opencv/highgui.h"

typedef unsigned int uint;

class ColorsTrasholds
{
public:
    uint h_top;
    uint s_top;
    uint v_top;
    uint h_bottom;
    uint s_bottom;
    uint v_bottom;

};

class ColorsStorage
{


    uint h_trashold;
    uint s_trashold;
    uint v_trashold;
    std::vector <ColorsTrasholds> etalon_marker_colors;
public:
    ColorsStorage(uint h_trashols, uint s_trashold, uint v_trashold );
    void setEtalon(const IplImage*, std::vector <CvPoint> init_markers_position);
    std::vector <ColorsTrasholds> getColors() const;
};

#endif // COLORSSTORAGE_H
