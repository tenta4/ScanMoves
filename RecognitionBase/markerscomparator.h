#ifndef MARKERSCOMPARATOR_H
#define MARKERSCOMPARATOR_H

#include "MarkersStorage/markersstorage.h"
#include "QDebug"
class MarkersComparator
{
    MarkersStorage *etal_ms;
    int curr_pos;
    const static int check_count = 3;
public:
    void compare(const std::vector <Marker>& user_frame, std::vector <Marker>& etal_frame, int& result_id);
    MarkersComparator(const MarkersStorage etalon);

    static float compare(MarkersStorage etalon_movement,
                         MarkersStorage user_movement,
                         std::vector <int>& corresponds_indexes);
    static float compare(std::vector <Marker> etalon,
                         std::vector <Marker> user);
};

#endif // MARKERSCOMPARATOR_H
