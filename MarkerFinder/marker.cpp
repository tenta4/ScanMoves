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
