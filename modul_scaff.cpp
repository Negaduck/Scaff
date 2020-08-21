#include "modul_scaff.h"

#include <iostream>

modul_scaff::modul_scaff(m_input user_input): material({0,{0,0,0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}),
                                              /*weight({3.9,{3.0,5.4,7.7,10.0,12.4,14.8,19.3},{4.0,5.8,7.6,9.5,11.4},
                                                     {7.5,8.0,8.9,9.9,10.5},{8.4,11.8,15.8,18.8,22.0}}),*/
                                              long_side(side()),
                                              wide_side(side()),
                                              user(user_input),
                                              fh(frame_height::normal),
                                              floors(0)
{
    set_floors();

}


//Still profuction code
void modul_scaff::set_floors(){
    if(user.height % 200) {
        int rest_height = user.height % 200;
        floors = user.height / 200;
        if(rest_height <= 50) {
            //set_fields();
        } else if(rest_height >= 51 && rest_height <= 100) {
            floors+=1;
            fh = mini;
            //set_fields();
        } else if(rest_height >= 101 && rest_height <= 150) {
            floors+=1;
            fh = frame_height::small;
            //set_fields();
        } else if(rest_height >= 151) {
            floors+=1;
            fh = medium;
            //set_fields();
        }
    } else {
        floors = user.height / 200;
        //set_fields();
    }
    std::cout << "Lagen: " << floors << std::endl;
}
