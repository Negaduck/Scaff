#ifndef MODUL_SCAFF_H
#define MODUL_SCAFF_H

#include "scaff.h"

struct side{
    bay_width bw[2];
    int bays,short_bays;
    int length;
    side() = default;
};

struct m_input  {
    int width, height,
        length,load_class;
    m_input()= default;
};

template<typename T>
struct m_components{
    int base_jack;
    int stalk[7];
    int bolt[5];
    int dia[5];
    int plank[5];
};

class modul_scaff{
private:
    m_components<int> material;
    m_components<double> weight;
    side long_side;
    side wide_side;
    m_input user;
    frame_height fh;
    int floors;
public:
    explicit modul_scaff(m_input user_input);
    void set_floors();
private:

};


#endif //MODUL_SCAFF_H
