#include "markerscomparator.h"

MarkersComparator::MarkersComparator(const MarkersStorage etalon)
{
    etal_ms = new MarkersStorage(etalon);
    curr_pos = 0;
}

void MarkersComparator::compare(const std::vector<Marker> &user_frame, std::vector <Marker>& etal_frame, int & found_id)
{

    const std::vector <std::vector <Marker> > etalon_v_v = etal_ms->getMarkersVector();

    int check_count = 7;
    float rating[check_count];
    for (int j = 0 ; j < check_count ; j++) rating[j] = 0;

    for (int j = curr_pos ; ( j < curr_pos + check_count ) && ( j < etalon_v_v.size() ) ; j++)
    {
        std::vector <Marker> etal_ms_vec = etalon_v_v.at(j);
        rating[j - curr_pos] = compare(etal_ms_vec, user_frame);
    }

    int max_id = 0;
    for (int j = 0 ; j < check_count ; j++)
    {
       if (rating[j] > rating[max_id])
            max_id = j;
    }

    curr_pos = curr_pos + max_id;
    qDebug()<<curr_pos<<"comparator"<< rating[max_id];


    found_id = curr_pos;
    if (curr_pos == etalon_v_v.size()-1) found_id = -1;


    int result_id = curr_pos+check_count;
    result_id = ( result_id > etalon_v_v.size()-1) ? (etalon_v_v.size()-1) : result_id ;

    etal_frame = etalon_v_v.at(result_id);

}

float MarkersComparator::compare(MarkersStorage etalon_movement,
                                 MarkersStorage user_movement,
                                 std::vector <int>& corresponds_indexes)
{
    std::vector <std::vector <Marker> > etalon_ms = etalon_movement.getMarkersVector();
    std::vector <std::vector <Marker> > user_ms = user_movement.getMarkersVector();


    int curr_pos = 0;
    int check_count = 5;
    float result = 0;
    for ( int i = 0 ; i < user_ms.size() ; i++)
    {
        std::vector <Marker> user_ms_vec = user_ms.at(i);
        float rating[check_count];
        for (int j = 0 ; j < check_count ; j++) rating[j] = 0;

        for (int j = curr_pos ; ( j < curr_pos + check_count ) && ( j < etalon_ms.size() ) ; j++)
        {
            std::vector <Marker> etal_ms_vec = etalon_ms.at(j);
            rating[j - curr_pos] = compare(etal_ms_vec, user_ms_vec);
        }

        int max_id = 0;
        for (int j = 0 ; j < check_count ; j++)
        {
            //qDebug()<<rating[j];
            if (rating[j] > rating[max_id])
                max_id = j;
        }
        result += rating[max_id];
        curr_pos = curr_pos + max_id;

        corresponds_indexes.push_back(curr_pos);

        qDebug()<<"user frame"<<i <<"etalon_frame"<< curr_pos;
    }
    return result/user_ms.size();
}

float MarkersComparator::compare(std::vector<Marker> etalon, std::vector<Marker> user)
{

    float max_res = 500000;

    float user_res = 0 ;

    for (int i = 0 ; i < user.size() ; i++)
    {
        Marker m_u = user.at(i);
        for (int j = 0 ; j < etalon.size() ; j++)
        {
            Marker m_e = etalon.at(j);
            if (m_e.id_marker == m_u.id_marker)
            {
                user_res += fabs(m_e.angle_x - m_u.angle_x) * 1000;
                user_res += fabs(m_e.angle_y - m_u.angle_y) * 1000;
                user_res += fabs(m_e.coord_z - m_u.coord_z);
            }

        }
    }
    user_res /= user.size() + 1;


    return (1 - user_res / max_res);
}
