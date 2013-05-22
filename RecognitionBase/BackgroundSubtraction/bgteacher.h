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
    const int* getMiddle();
    BGTeacher(int width, int height);
    ~BGTeacher();
    void push(IplImage *);
    void calc();
    CvSize getBgSize();

};

#endif // BGTEACHER_H
