#include "bgteacher.h"

BGTeacher::BGTeacher(int w, int h)
{
    bg_size = cvSize(w,h);
    middle_bg = 0;
}

void BGTeacher::push(IplImage * input_img)
{
    if (input_img->width!= bg_size.width || input_img->height != bg_size.height)
        throw std::out_of_range("resolution error in BGTeacher");

    IplImage* tmp = cvCreateImage(cvGetSize(input_img), 8, 3);
    cvCopy(input_img,tmp);
    images.push_back(tmp);
}

void BGTeacher::calc()
{
    if (images.size() == 0)
    {
        if (middle_bg == 0) throw std::out_of_range("You have not background images");
        else return;
    }

    delete [] middle_bg;
    middle_bg = new int[bg_size.height*bg_size.width*3];

    int i,j,i1,j1;
    uchar* ptr;

    for ( i = 0; i < bg_size.height ; i++)
          for( j = 0; j < bg_size.width  ; j++)
                for( j1 = 0; j1 < 3 ; j1++ )
                {
                      middle_bg[(i*bg_size.width+j)*3+j1]=0;
                      for( i1=0 ; i1 < images.size() ; i1++)
                      {
                           ptr = (uchar*) (images[i1]->imageData);
                           middle_bg[(i*bg_size.width+j)*3+j1]+=ptr[(i*bg_size.width+j)*3+j1];

                      }
                      middle_bg[(i*bg_size.width+j)*3+j1]=middle_bg[(i*bg_size.width+j)*3+j1]/images.size();
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
CvSize BGTeacher::getBgSize()
{
    return bg_size;
}

BGTeacher::~BGTeacher()
{
    delete [] middle_bg;
}

