#include "markerfinder.h"
#include "QDebug"

void MarkerFinder::recursion(int x, int y, uchar* ptr)
{
    if ((x>(image_width-1))||x<0||(y>(image_height-1))||y<0||m.size>30000) return;

    if (ptr[y*image_width+x]==m.id_marker)
    {
        m.size++;
        if (m.left.x>x)     {   m.left.x=x; m.left.y=y;}
        else if (m.rihgt.x<x){  m.rihgt.x=x;m.rihgt.y=y;}
        else if (m.top.y>y) {   m.top.y=y;  m.top.x=x;}
        else if (m.buttom.y<y){ m.buttom.y=y;m.buttom.x=x;}

        ptr[y*image_width+x]= FLAG_FULL;

        recursion(x+1,y,ptr);
        recursion(x-1,y,ptr);
        recursion(x,y+1,ptr);
        recursion(x,y-1,ptr);
    }
}

void MarkerFinder::inRange(IplImage *src, std::vector <CvScalar> colors, int range, IplImage *dst)
{
    if (dst->nChannels != 1 || src->width != dst->width || src->height != dst->height) throw cv::Exception();
    unsigned char *p_img = (unsigned char*)src->imageData;
    int w = src->width;
    int h = src->height;
    int imul = 3 ;
    for (int i = 0; i < w ; i++)
        for (int j = 0 ; j< h ; j++)
            for (int k = 0 ; k< colors.size() ; k++)
            if (p_img[(j*src->width+i)*3]   > (colors.at(k).val[0]- range)   && p_img[(j*src->width+i)*3]   < (colors.at(k).val[0]+ range))
            if (p_img[(j*src->width+i)*3+1] > (colors.at(k).val[1]- range*imul) && p_img[(j*src->width+i)*3+1] < (colors.at(k).val[1]+ range*imul))
            if (p_img[(j*src->width+i)*3+2] > (colors.at(k).val[2]- range*imul) && p_img[(j*src->width+i)*3+2] < (colors.at(k).val[2]+ range*imul))
                dst->imageData[j*src->width+i] = k;
}

std::vector <Marker> MarkerFinder::getMarkers(IplImage *img, const ColorsStorage* colors_to_find)
{
    image_width = img->width;
    image_height = img->height;
    IplImage* Thresholdimg = cvCreateImage(cvGetSize(img), 8, 1);
    memset(Thresholdimg->imageData,FLAG_EMPTY,Thresholdimg->width*Thresholdimg->height*Thresholdimg->nChannels);
    inRange(img, colors_to_find->getColors(), 20 , Thresholdimg);


    int step = 4;
    for (int i = 0;i< img->width; i+=step)
        for (int j = 0; j<img->height; j+=step)
        {

            uchar * ptr = (uchar*)Thresholdimg->imageData;
            m.size = 0;

            if (ptr[j*img->width+i]<FLAG_FULL)
            {
                m = Marker(ptr[j*img->width+i]);
                recursion(i,j,ptr);
            }
            if (m.size<200) continue;

            cvDrawCircle(img,m.left,5,cvScalar(128),2);
            cvDrawCircle(img,m.rihgt,5,cvScalar(128),2);
            cvDrawCircle(img,m.top,5,cvScalar(128),2);
            cvDrawCircle(img,m.buttom,5,cvScalar(128),2);

            cvDrawLine(img,m.left,m.top,cvScalar(128),2);
            cvDrawLine(img,m.top,m.rihgt,cvScalar(128),2);
            cvDrawLine(img,m.buttom,m.rihgt,cvScalar(128),2);
            cvDrawLine(img,m.left,m.buttom,cvScalar(128),2);


            std::cerr<<"dist"<<m.calcDistance()<<"\n";

      //      qDebug()<<m.size<<"-----------------";
      //      qDebug()<<"left"<<m.left.x<<m.left.y<<ptr[m.left.y*img->width+m.left.x];
         //   while (cvWaitKey(20)<0)cvShowImage("ww",img);
        }

    cvShowImage("tr",Thresholdimg);
    cvShowImage("result",img);
//    qDebug()<<(int)img->imageData[(240*640+320)*3]<<(int)img->imageData[(240*640+320)*3+1]<<(int)img->imageData[(240*640+320)*3+2];

    cvReleaseImage(&Thresholdimg);
    std::vector <Marker> vec;
    return vec;
}
