#ifndef BGDETECTOR_H
#define BGDETECTOR_H
#include "vector"
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "bgteacher.h"

class BGDetector
{
public:

    BGDetector(BGTeacher* bgteacher, int threshold, int square_size);
    void checkImg(IplImage*);
    ~BGDetector();

private:
    int square;
    int threshold;
    BGTeacher* bgteacher;
};

#endif // BGDETECTOR_H
