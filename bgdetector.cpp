#include "bgdetector.h"

BGDetector::BGDetector(int threshold):threshold(threshold)
{
    mid = 0;
}

void BGDetector::push(IplImage * input_img)
{
    images.push_back(input_img);
}

void BGDetector::calc()
{
    if (images.size() == 0)
    {
        if (mid == 0) throw std::out_of_range("You have not background images");
        else return;
    }

    delete [] mid;
    mid=new int[images[0]->height*images[0]->width*3];

    int i,j,i1,j1;
    uchar* ptr;

    for(i=0;i<images[0]->height;i++)
          for(j=0;j<images[0]->width;j++)
                for(j1=0;j1<3;j1++)
                {
                      mid[(i*images[0]->width+j)*3+j1]=0;
                      for(i1=0;i1<images.size();i1++)
                      {
                           ptr = (uchar*) (images[i1]->imageData);
                           mid[(i*images[0]->width+j)*3+j1]+=ptr[j*3+i*images[i1]->widthStep+j1];

                      }
                      mid[(i*images[0]->width+j)*3+j1]=mid[(i*images[0]->width+j)*3+j1]/images.size();
                }

    for (int i = 0 ; i < images.size() ; i++)
    {
        cvReleaseImage(&images.at(i));
    }
    images.clear();
    std::cerr<<images.size()<<"fsdfs";
}


BGDetector::~BGDetector()
{
    delete [] mid;
}
void BGDetector::checkImg(IplImage * image1)
{
    if (mid == 0) throw std::out_of_range("You have not background images");

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
                        k+=(abs(mid[((i+ii)*image1->width+j+jj)*3+0]-ptr[(j+jj)*3+(i+ii)*image1->widthStep+0]));
                        k+=(abs(mid[((i+ii)*image1->width+j+jj)*3+1]-ptr[(j+jj)*3+(i+ii)*image1->widthStep+1])/3);
                        k+=(abs(mid[((i+ii)*image1->width+j+jj)*3+2]-ptr[(j+jj)*3+(i+ii)*image1->widthStep+2])/3);

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

