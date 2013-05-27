#include "markersio.h"
#include "QDebug"
MarkersIO::MarkersIO()
{
}

void MarkersIO::saveMovement(
        const char *name,
        const MarkersStorage markers_storage,
        const std::vector<IplImage *> images)
{
    mkdir(name);
    char tmp_name[255];
    for (int i = 0 ; i < images.size() ; i++)
    {
        sprintf(tmp_name,"%s\\%d.png",name,i);
        cvSaveImage(tmp_name, images.at(i));

    }


    sprintf(tmp_name,"%s\\%s.txt",name,name);

    const std::vector <std::vector <Marker> >   markers = markers_storage.getMarkersVector();

    std::ofstream file;
    file.open(tmp_name);


    file<<markers.size()<<std::endl;

    for (int i = 0 ; i < markers.size() ; i++)
    {
        std::vector <Marker> markers_vec = markers.at(i);

        file << markers_vec.size() << "\t";

        for (int j = 0 ; j < markers_vec.size() ; j++)
        {
            Marker tmp_marker = markers_vec.at(j);
            file << tmp_marker.id_marker << " ";
            file << tmp_marker.angle_x   << " ";
            file << tmp_marker.angle_y   << " ";
            file << tmp_marker.coord_z   << " ";

        }
        file << std::endl;
    }
    file.close();

}

void MarkersIO::openMovement(const char *name, MarkersStorage &markers)
{
    char tmp_name[256];

    sprintf(tmp_name,"%s\\%s.txt",name,name);

    std::ifstream file;
    file.open(tmp_name);

    int frame_count = 0;
    file >> frame_count;

    for (int i = 0 ; i < frame_count ; i++)
    {
        std::vector <Marker> markers_vec;
        int markers_count = 0;
        file >> markers_count;
        for (int j = 0 ; j < markers_count ; j++)
        {
            Marker m;
            file >> m.id_marker;
            file >> m.angle_x;
            file >> m.angle_y;
            file >> m.coord_z;
            markers_vec.push_back(m);
        }
        markers.pushMarkers(markers_vec);
    }
    file.close();
}

void MarkersIO::openMovement(const char *name, MarkersStorage& markers, std::vector<IplImage *>& images)
{


    openMovement(name, images);
    openMovement(name, markers);
}

void MarkersIO::openMovement(const char *name, std::vector<IplImage *> &images)
{
    char tmp_name[255];

    for (int i = 0 ; 1 ; i++)
    {
        sprintf(tmp_name,"%s\\%d.png",name,i);
        IplImage* img = cvLoadImage(tmp_name);
        if (!img) break;
        images.push_back(img);

    }

}
