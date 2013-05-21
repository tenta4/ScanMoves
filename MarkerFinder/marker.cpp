#include "marker.h"

Marker::Marker()
{
}
Marker::Marker(int id):id_marker(id)
{
    acreage = 0;
    left    = cvPoint(1e5 ,  0 );
    rihgt   = cvPoint(0   ,  0 );
    top     = cvPoint(0   , 1e5);
    buttom  = cvPoint(0   , 0  );
}

float Marker::getMaxWidth()
{
    float screen_size1 = sqrt ((left.x-rihgt.x)*(left.x-rihgt.x)+(left.y-rihgt.y)*(left.y-rihgt.y));
    float screen_size2 = sqrt ((top.x-buttom.x)*(top.x-buttom.x)+(top.y-buttom.y)*(top.y-buttom.y));
    return ( screen_size1>screen_size2 ? screen_size1 : screen_size2);

}

