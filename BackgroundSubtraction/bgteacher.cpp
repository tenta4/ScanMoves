#include "bgteacher.h"

void BGTeacher::push(IplImage * input_img)
{
    IplImage* tmp = cvCreateImage(cvGetSize(input_img), 8, 3);
    cvCopy(input_img,tmp);
    bg_size = cvGetSize(tmp);
    images.push_back(tmp);
}
BGTeacher::BGTeacher()
{
    middle_bg = 0;
}
BGTeacher::~BGTeacher()
{
    delete [] middle_bg;
}
void BGTeacher::calc()
{
    if (images.size() == 0)
    {
        if (middle_bg == 0) throw std::out_of_range("You have not background images");
        else return;
    }

    delete [] middle_bg;
    middle_bg = new int[images[0]->height*images[0]->width*3];

    int i,j,i1,j1;
    uchar* ptr;

    for(i=0;i<images[0]->height;i++)
          for(j=0;j<images[0]->width;j++)
                for(j1=0;j1<3;j1++)
                {
                      middle_bg[(i*images[0]->width+j)*3+j1]=0;
                      for(i1=0;i1<images.size();i1++)
                      {
                           ptr = (uchar*) (images[i1]->imageData);
                           middle_bg[(i*images[0]->width+j)*3+j1]+=ptr[j*3+i*images[i1]->widthStep+j1];

                      }
                      middle_bg[(i*images[0]->width+j)*3+j1]=middle_bg[(i*images[0]->width+j)*3+j1]/images.size();
                }

    for (int i = 0 ; i < images.size() ; i++)
    {
        cvReleaseImage(&images.at(i));
    }
    images.clear();
}

int* BGTeacher::getMiddle()
{
    return middle_bg;
}
