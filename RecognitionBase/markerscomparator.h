#ifndef MARKERSCOMPARATOR_H
#define MARKERSCOMPARATOR_H

#include "MarkersStorage/markersstorage.h"
#include "QDebug"
class MarkersComparator
{
public:
    static float compare(MarkersStorage etalon_movement,
                         MarkersStorage user_movement,
                         std::vector <int>& corresponds_indexes);
    static float compare(std::vector <Marker> etalon,
                         std::vector <Marker> user);
};

#endif // MARKERSCOMPARATOR_H
