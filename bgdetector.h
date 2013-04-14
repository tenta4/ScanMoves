#ifndef BGDETECTOR_H
#define BGDETECTOR_H
#include "vector"
#include "opencv/highgui.h"
#include "opencv/cv.h"
class BGDetector
{
public:
    BGDetector(int);
    void push(IplImage *);
    void calc();
    void checkImg(IplImage*);
    ~BGDetector();

private:
    int threshold;
    int *mid;
    std::vector <IplImage*> images;

};

#endif // BGDETECTOR_H
