#include "markersstorage.h"
#include "QDebug"
MarkersStorage::MarkersStorage(CvSize2D32f camera_angles, CvSize2D32f image_resol,float markers_real_size):
    camera_angles(camera_angles), image_resol(image_resol),markers_real_size(markers_real_size)
{
    half_camera_ang = cvSize2D32f(camera_angles.width / 2, camera_angles.height / 2 );
    half_image_size = cvSize2D32f(image_resol.width / 2  , image_resol.height  / 2 );

}

void MarkersStorage::pushPolarMarkers(std::vector<Marker> input_markers)
{
    all_video_markers.push_back(input_markers);

}

std::vector <Marker> MarkersStorage::pushImageMarkers(std::vector<Marker> input_markers)
{
    for (int j = 0 ; j < input_markers.size() ; j++)
    {
        Marker &tmp_marker = input_markers.at(j);

        CvPoint marker_center;
        marker_center.x = ( tmp_marker.rihgt.x + tmp_marker.left.x ) / 2.0 ;
        marker_center.y = ( tmp_marker.rihgt.y + tmp_marker.left.y ) / 2.0 ;

        tmp_marker.angle_y = ( marker_center.x - half_image_size.width ) /
                half_image_size.width  * half_camera_ang.width ;

        tmp_marker.angle_x = ( marker_center.y - half_image_size.height)
                / half_image_size.height * half_camera_ang.height;

        //todo - calc, using camera angles
        tmp_marker.coord_z = 710.0 * markers_real_size / tmp_marker.getMaxWidth();

//        qDebug()<<"*************";
//        qDebug()<< "left x,y "<<tmp_marker.left.x   <<tmp_marker.left.y;
//        qDebug()<< "right x,y"<<tmp_marker.rihgt.x  <<tmp_marker.rihgt.y;
//        qDebug()<< "center"   <<marker_center.x     <<marker_center.y;
//        qDebug()<< "pol id="  <<tmp_marker.id_marker<<"x,y,z ="<< tmp_marker.angle_x << tmp_marker.angle_y << tmp_marker.coord_z;

    }

    all_video_markers.push_back(input_markers);
    return input_markers;
}

MarkersStorage::~MarkersStorage()
{

}

void MarkersStorage::convertToImageCS()
{

    for (int i = 0 ; i < all_video_markers.size() ; i++)
    {
        std::vector <Marker> marker_vec = all_video_markers.at(i);
        for (int j = 0 ; j < marker_vec.size() ; j++)
        {
            Marker m = marker_vec.at(j);
            CvPoint marker_center;
            marker_center.x = m.angle_y / half_camera_ang.width * half_image_size.width + half_image_size.width;
            marker_center.y = m.angle_x / half_camera_ang.height* half_image_size.height+ half_image_size.height;

            //todo - calc, using camera angles
            float markers_half_width = 710.0 * markers_real_size / m.coord_z / 2;

            m.left   = cvPoint( marker_center.x - markers_half_width, marker_center.y);
            m.rihgt  = cvPoint( marker_center.x + markers_half_width, marker_center.y);
            m.top    = cvPoint( marker_center.x, marker_center.y - markers_half_width);
            m.buttom = cvPoint( marker_center.x, marker_center.y + markers_half_width);

            marker_vec.at(j) = m ;
            //qDebug()<<marker_center.x<<marker_center.y<<markers_half_width<<(m.angle_y / half_camera_ang.width * half_image_size.width + half_image_size.width);
        }
        all_video_markers.at(i) = marker_vec;
    }

}
void MarkersStorage::clearStorage()
{
    all_video_markers.clear();
}

