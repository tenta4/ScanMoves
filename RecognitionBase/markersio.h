#ifndef MARKERSIO_H
#define MARKERSIO_H

#include "vector"
#include "marker.h"
#include "fstream"
#include "dir.h"


class MarkersIO
{
public:
    MarkersIO();
    static void saveMovement(
            const char * name,
            const std::vector <std::vector <Marker> > markers,
            const std::vector <IplImage*>);

    static void openMovement(
            const char * name,
            std::vector <std::vector <Marker> > markers,
            std::vector <IplImage*>);
};

#endif // MARKERSIO_H
