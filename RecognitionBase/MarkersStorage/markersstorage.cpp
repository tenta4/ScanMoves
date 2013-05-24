#include "markersstorage.h"
#include "QDebug"
MarkersStorage::MarkersStorage(float focal_length, float markers_real_size):
    focal_length(focal_length), markers_real_size(markers_real_size)
{

}

void MarkersStorage::pushMarkers(std::vector<Marker> input_markers)
{
    all_video_markers.push_back(input_markers);
}

MarkersStorage::~MarkersStorage()
{

}

const std::vector <std::vector <Marker> >  MarkersStorage::getMarkers()
{
    std::vector <std::vector <Marker> >  tmp_markers_vec_vec;

    CvSize2D32f  half_image_size    = cvSize2D32f(320 , 240 );
    CvSize2D32f  half_camera_angles = cvSize2D32f(30.0, 22.0);

    qDebug()<<"********************************************************";

    for (int j = 0 ; j < all_video_markers.size() ; j++)
    {
        std::vector <Marker> tmp_markers_vec = all_video_markers.at(j);

        for (int i = 0 ; i < tmp_markers_vec.size() ; i++)
        {
            Marker tmp_marker = tmp_markers_vec.at(i);

            CvPoint marker_center;
            marker_center.x = ( tmp_marker.rihgt.x + tmp_marker.left.x ) / 2.0 ;
            marker_center.y = ( tmp_marker.rihgt.y + tmp_marker.left.y ) / 2.0 ;

            tmp_marker.angle_y = ( marker_center.x - half_image_size.width ) /
                    half_image_size.width  * half_camera_angles.width ;

            tmp_marker.angle_x = ( marker_center.y - half_image_size.height)
                    / half_image_size.height * half_camera_angles.height;

            tmp_marker.coord_z = focal_length * markers_real_size / tmp_marker.getMaxWidth();

            qDebug()<<"*************";
            qDebug()<< "left x,y "<<tmp_marker.left.x   <<tmp_marker.left.y;
            qDebug()<< "right x,y"<<tmp_marker.rihgt.x  <<tmp_marker.rihgt.y;
            qDebug()<< "center"   <<marker_center.x     <<marker_center.y;
            qDebug()<< "pol id="  <<tmp_marker.id_marker<<"x,y,z ="<< tmp_marker.angle_x << tmp_marker.angle_y << tmp_marker.coord_z;

            tmp_markers_vec.at(i) = tmp_marker;
        }
        tmp_markers_vec_vec.push_back(tmp_markers_vec);
    }
    return tmp_markers_vec_vec;
}