#include "markerscomparator.h"


float MarkersComparator::compare(MarkersStorage etalon_movement, MarkersStorage& user_movement)
{
    std::vector <std::vector <Marker> > etalon_ms = etalon_movement.getMarkersVector();
    std::vector <std::vector <Marker> >& user_ms = user_movement.getMarkersVector();

    int curr_pos = 0;
    int check_count = 10;
    float result = 0;
    for ( int i = 0 ; i < user_ms.size() ; i++)
    {
        std::vector <Marker> user_ms_vec = user_ms.at(i);
        float rating[check_count];
        for (int j = 0 ; j < check_count ; j++) rating[j] = 1e10;

        for (int j = curr_pos ; ( j < curr_pos + check_count ) && ( j < etalon_ms.size() ) ; j++)
        {
            std::vector <Marker> etal_ms_vec = etalon_ms.at(j);
            rating[j - curr_pos] = compare(etal_ms_vec, user_ms_vec);
        }

        int min_id = 0;
        for (int j = 0 ; j < check_count ; j++)
        {
            qDebug()<<rating[j];
            if (rating[j] < rating[min_id])
                min_id = j;
        }
        result += rating[min_id];
        curr_pos = curr_pos + min_id;

        for (int j = 0 ; j < etalon_ms.at(curr_pos).size() ; j++) user_ms.at(i).push_back(etalon_ms.at(curr_pos).at(j));
        qDebug()<<"user frame"<<i <<"etalon_frame"<< curr_pos;
    }
    return result;
}

float MarkersComparator::compare(std::vector<Marker> etalon, std::vector<Marker> user)
{
    float return_res = 0 ;

    for (int i = 0 ; i < user.size() ; i++)
    {
        Marker m_u = user.at(i);
        for (int j = 0 ; j < etalon.size() ; j++)
        {
            Marker m_e = etalon.at(j);
            if (m_e.id_marker == m_u.id_marker)
            {
                float result = 0;
                result += fabs(m_e.angle_x - m_u.angle_x) * 1000;
                result += fabs(m_e.angle_y - m_u.angle_y) * 1000;
                result += fabs(m_e.coord_z - m_u.coord_z);

                return_res += result;
            }
        }
    }
//    return_res /= user.size();
    return return_res;
}
