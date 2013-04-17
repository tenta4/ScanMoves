#ifndef BGDETECTOR_H
#define BGDETECTOR_H
#include "vector"
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "bgteacher.h"

class BGDetector
{
public:

    BGDetector(BGTeacher*, int);
    void checkImg(IplImage*);
    ~BGDetector();

private:
    int threshold;
    BGTeacher* bgteacher;
};

#endif // BGDETECTOR_H
