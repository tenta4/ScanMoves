#ifndef MARKERSIO_H
#define MARKERSIO_H

#include "vector"
#include "MarkersStorage/markersstorage.h"
#include "fstream"
#include "dir.h"


class MarkersIO
{
public:
    MarkersIO();
    static void saveMovement(
            const char * name,
            const MarkersStorage markers,
            const std::vector <IplImage*>);

    static void openMovement(
            const char * name,
            MarkersStorage markers,
            std::vector <IplImage*>);
};

#endif // MARKERSIO_H
