#ifndef BGTEACHER_H
#define BGTEACHER_H
#include "vector"
#include "opencv/highgui.h"
#include <stdexcept>

class BGTeacher
{
    std::vector <IplImage*> images;
    CvSize bg_size;
    int *middle_bg;
public:
    int *getMiddle();
    BGTeacher();
    ~BGTeacher();
    void push(IplImage *);
    void calc();

};

#endif // BGTEACHER_H
