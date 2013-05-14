#include "markerfinder.h"
#include "QDebug"

MarkerFinder::MarkerFinder(CvSize size)
{
    tmp_graystyle_image = cvCreateImage(size, 8, 1);
    image_width  = size.width;
    image_height = size.height;

}

void MarkerFinder::recursion(int x, int y, uchar* ptr, FROM_WHERE_COME_IN from_where)
{
    if ((x>(image_width-1))||x<0||(y>(image_height-1))||y<0||m.size>30000) return;

    int position = y*image_width+x;

    if (ptr[ position ]==m.id_marker)
    {
        m.size++;

        switch (from_where)
        {
            case FROM_LEFT :
            {
                if ( m.rihgt.x < x )    { m.rihgt.x = x;   m.rihgt.y = y;}

                ptr[ position ]= FLAG_FULL;

                recursion(x + 1 , y     , ptr , FROM_LEFT);
                recursion(x     , y + 1 , ptr , FROM_TOP);
                recursion(x     , y - 1 , ptr , FROM_BOTTOM);
                break;
            }
            case FROM_RIGHT :
            {
                if ( m.left.x > x )     { m.left.x = x;     m.left.y = y;}

                ptr[ position]= FLAG_FULL;

                recursion(x - 1 , y     ,ptr, FROM_RIGHT);
                recursion(x     , y + 1 ,ptr, FROM_TOP);
                recursion(x     , y - 1 ,ptr, FROM_BOTTOM);
                break;
            }
            case FROM_TOP :
            {
                if ( m.buttom.y < y )   { m.buttom.y = y;   m.buttom.x = x;}

                ptr[ position ]= FLAG_FULL;

                recursion(x + 1 , y     ,ptr, FROM_LEFT);
                recursion(x - 1 , y     ,ptr, FROM_RIGHT);
                recursion(x     , y + 1 ,ptr, FROM_TOP);
                break;
            }
            case FROM_BOTTOM :
            {
                if (m.top.y > y)        { m.top.y = y;      m.top.x = x;}

                ptr[ position ]= FLAG_FULL;

                recursion(x + 1 , y     ,ptr, FROM_LEFT);
                recursion(x - 1 , y     ,ptr, FROM_RIGHT);
                recursion(x     , y - 1 ,ptr, FROM_BOTTOM);
                break;
            }
            case FROM_CENTER :
            {
                m.top.y     = y; m.top.x    = x;
                m.buttom.y  = y; m.buttom.x = x;
                m.left.y    = y; m.rihgt.x  = x;
                m.rihgt.y   = y; m.left.x   = x;

                ptr[ position ]= FLAG_FULL;

                recursion(x+1,y,ptr, FROM_LEFT);
                recursion(x-1,y,ptr, FROM_RIGHT);
                recursion(x,y+1,ptr, FROM_TOP);
                recursion(x,y-1,ptr, FROM_BOTTOM);
            }
        }   // end switch
    }       // end if marker color found
}           // end function

void MarkerFinder::inRange(IplImage *src, std::vector <CvScalar> colors, int range, IplImage *dst)
{

    unsigned char *p_img = (unsigned char*)src->imageData;

    int imul = 3 ;
    for (int j = 0 ; j< image_height ; j++)
    {
        int pos = j * image_width ;

        for (int i = 0; i < image_width ; i++)
        {
            int pos_lvl2 = ( pos + i ) * 3;
            for (int k = 0 ; k< colors.size() ; k++)
            if (p_img[pos_lvl2    ] > (colors.at(k).val[0]- range)      && p_img[ pos_lvl2   ] < (colors.at(k).val[0]+ range))
            if (p_img[pos_lvl2 + 1] > (colors.at(k).val[1]- range*imul) && p_img[ pos_lvl2 +1] < (colors.at(k).val[1]+ range*imul))
            if (p_img[pos_lvl2 + 2] > (colors.at(k).val[2]- range*imul) && p_img[ pos_lvl2 +2] < (colors.at(k).val[2]+ range*imul))
                dst->imageData[ pos + i ] = k;
        }
    }
}

std::vector <Marker> MarkerFinder::getMarkers(IplImage *img, const ColorsStorage* colors_to_find)
{

    std::vector <Marker> found_markers;

    memset(tmp_graystyle_image->imageData,FLAG_EMPTY, image_width * image_height );

    inRange(img, colors_to_find->getColors(), 20 , tmp_graystyle_image);

    int step = 8;
    for (int i = 0;i< img->width; i+=step)
        for (int j = 0; j<img->height; j+=step)
        {

            uchar * ptr = (uchar*)tmp_graystyle_image->imageData;
            m.size = 0;

            if (ptr[j*img->width+i]<FLAG_FULL)
            {
                m = Marker(ptr[j*img->width+i]);
                recursion(i,j,ptr, FROM_CENTER);
            }
            if (m.size<200) continue;

            m.calcDistance();

            found_markers.push_back(m);
        }

    //cvShowImage("tr",tmp_graystyle_image);

    return found_markers;
}

MarkerFinder::~MarkerFinder()
{
    cvReleaseImage(&tmp_graystyle_image);

}
