#ifndef MARKERSCOMPARATOR_H
#define MARKERSCOMPARATOR_H

#include "MarkersStorage/markersstorage.h"
#include "QDebug"
class MarkersComparator
{
public:
    static float compare(MarkersStorage etalon_movement, MarkersStorage& user_movement);
    static float compare(std::vector <Marker>, std::vector <Marker>);
};

#endif // MARKERSCOMPARATOR_H
