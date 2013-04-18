#include "bgdetector.h"


BGDetector::BGDetector(BGTeacher* bgt, int t, int sq) : threshold(t)
{
    if (sq > 40)                throw std::out_of_range("to big square value");
    if (bgt == 0)               throw std::out_of_range("Bgteacher* = 0");
    if (bgt->getMiddle() == 0)  throw std::out_of_range("You have not background images");

    square    = sq;
    bgteacher = bgt;

}

BGDetector::~BGDetector()
{

}
void BGDetector::checkImg(IplImage * image)
{
    int i,j,j1;
    uchar* ptr;

    ptr = (uchar*) (image->imageData);
    for(i=0;i<image->height;i+=square)
          for(j=0;j<image->width;j+=square)
          {
                int sum=0;

                for (int ii=0;ii<square;ii++)
                    for (int jj=0;jj<square;jj++)
                    {
                        sum+=(abs(bgteacher->getMiddle()[((i+ii)*image->width+j+jj)*3+0]-ptr[(j+jj)*3+(i+ii)*image->widthStep+0]));
                        sum+=(abs(bgteacher->getMiddle()[((i+ii)*image->width+j+jj)*3+1]-ptr[(j+jj)*3+(i+ii)*image->widthStep+1])/3);
                        sum+=(abs(bgteacher->getMiddle()[((i+ii)*image->width+j+jj)*3+2]-ptr[(j+jj)*3+(i+ii)*image->widthStep+2])/3);

                    }
                if (sum<=threshold*square*square)

                for (int ii=0;ii<square;ii++)
                    for (int jj=0;jj<square;jj++)
                        for(j1=0;j1<3;j1++){
                             if (j1==1) ptr[(j+jj)*3+(i+ii)*image->widthStep+j1]=0;
                             else ptr[(j+jj)*3+(i+ii)*image->widthStep+j1]=0;
                        }
          }

}

