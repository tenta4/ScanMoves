#include "markersstorage.h"
#include "dir.h"
#include "QDebug"
MarkersStorage::MarkersStorage(float focal_length, float markers_real_size):
    focal_length(focal_length), markers_real_size(markers_real_size)
{

}

void MarkersStorage::pushImage(IplImage * input_image)
{
    images.push_back(input_image);
}

void MarkersStorage::pushMarkers(std::vector<Marker> input_markers)
{
    CvSize2D32f  half_image_size    = cvSize2D32f(320 , 240 );
    CvSize2D32f  half_camera_angles = cvSize2D32f(30.0, 22.0);

    all_video_markers.push_back(input_markers);

    int count = input_markers.size();

    qDebug()<<"********************************************************";

    for (int i = 0 ; i < count ; i++)
    {
        MarkerPolarCS marker_pol;
        Marker simple_marker = input_markers.at(i);
        marker_pol.index     = simple_marker.id_marker;

        CvPoint marker_center;
        marker_center.x = ( simple_marker.rihgt.x + simple_marker.left.x ) / 2.0 ;
        marker_center.y = ( simple_marker.rihgt.y + simple_marker.left.y ) / 2.0 ;

        marker_pol.angle_y = ( marker_center.x - half_image_size.width ) /
                half_image_size.width  * half_camera_angles.width ;

        marker_pol.angle_x = ( marker_center.y - half_image_size.height)
                / half_image_size.height * half_camera_angles.height;

        marker_pol.coord_z = focal_length * markers_real_size / simple_marker.getMaxWidth();

        qDebug()<<"*************"<<focal_length<<markers_real_size;
        qDebug()<< "left x,y "<<simple_marker.left.x <<simple_marker.left.y;
        qDebug()<< "right x,y"<<simple_marker.rihgt.x<<simple_marker.rihgt.y;
        qDebug()<< "center"<< marker_center.x << marker_center.y;
        qDebug()<< "pol id=" <<marker_pol.index <<"x,y,z ="<< marker_pol.angle_x << marker_pol.angle_y << marker_pol.coord_z;
    }
}

void MarkersStorage::saveMovement(const char *name)
{
    mkdir(name);
}

MarkersStorage::~MarkersStorage()
{
    for (int i = 0 ; i < images.size() ; i++)
    {
        cvReleaseImage(&images.at(i));
    }
}
