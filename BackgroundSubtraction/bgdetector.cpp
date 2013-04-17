#include "bgdetector.h"


BGDetector::BGDetector(BGTeacher* bgt, int t) : bgteacher(bgt), threshold(t)
{

}

BGDetector::~BGDetector()
{

}
void BGDetector::checkImg(IplImage * image1)
{
    if (bgteacher->getMiddle() == 0) throw std::out_of_range("You have not background images");

    int i,j,j1;
    uchar* ptr;
    float k=0;

    int square=8;
    ptr = (uchar*) (image1->imageData);
    for(i=0;i<image1->height;i+=square)
          for(j=0;j<image1->width;j+=square)
          {
                k=0;

                for (int ii=0;ii<square;ii++)
                    for (int jj=0;jj<square;jj++)
                    {
                        k+=(abs(bgteacher->getMiddle()[((i+ii)*image1->width+j+jj)*3+0]-ptr[(j+jj)*3+(i+ii)*image1->widthStep+0]));
                        k+=(abs(bgteacher->getMiddle()[((i+ii)*image1->width+j+jj)*3+1]-ptr[(j+jj)*3+(i+ii)*image1->widthStep+1])/3);
                        k+=(abs(bgteacher->getMiddle()[((i+ii)*image1->width+j+jj)*3+2]-ptr[(j+jj)*3+(i+ii)*image1->widthStep+2])/3);

                    }
                if (k<=50*square*square)

                for (int ii=0;ii<square;ii++)
                    for (int jj=0;jj<square;jj++)
                        for(j1=0;j1<3;j1++){
                             if (j1==1) ptr[(j+jj)*3+(i+ii)*image1->widthStep+j1]=0;
                             else ptr[(j+jj)*3+(i+ii)*image1->widthStep+j1]=0;
                        }
          }

}

