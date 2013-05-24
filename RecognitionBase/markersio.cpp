#include "markersio.h"

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

    MarkersStorage ms(markers_storage);
    const std::vector <std::vector <Marker> >   markers = ms.getMarkersVector();

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
