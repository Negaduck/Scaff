#ifndef SCAFF_H
#define SCAFF_H

#include <string>

#include "umlaute.h"

//Needed input to calculate
//the components for the scaffold.
//is used as argument for scaff constructor
struct input {
    std::string name;
    int plank_choice,load_class;
    int height, lenght;
    input()=default;
};


template<typename T>
struct planks {
    T alu[5];
    T steel[5];
    T wodden[5];
    planks()=default;
};

template<typename T>
struct frames {
    T frame[4];
    T w_frame[4];
    frames()=default;
};

//All possible components
template<class T>
struct components {
    planks<T> pchoice;
    frames<T> fchoice;
    T guard[5];
    T t_board[5];
    T dia[5];
    T e_guard[2];
    T ladder[2];
    T b_jack;
    components()=default;
};


enum frame_width :
int {thin = 2,wide};
enum bay_width :
int {one,one_h,two,two_h,three};
enum frame_height:
int {mini,small,medium,normal};

//We represent Facadescaffold as class
class scaff {
private:
    components<double> weight;
    components<int> material;
    input u_input;
    int bays,short_bays,floors;
    bay_width bw[2];
    frame_height fh;
    frame_width fw;
public:
    explicit scaff(input u_input);
    ~scaff();
private:
    void set_floors();
    void set_fields();      //determines if we have 3m fields or not
    void short_fields();    //sets 2.5m fields and shorter
    void long_fields();     //sets 3m fields and shorter
    void set_frames();      //calculates the the frames
    void set_stamp();       //writes a material list in a file
    double set_stalkload(bay_width bw, int floors);     //calculates the forces under the base jack
    void first_print(FILE*);        //prints the first part of the calculated scaff
                                    // in the file
    void second_print(FILE*);       //prints the second part in the file
    void append_data(const char *data);
    double set_weight(components<int>& lhs,         //calculates the weight of the complete scaffold
                      components<double>& rhs);
    void one_field( frame_width f_choice,           //the fields set here are all of the same
                    bay_width b_choice);

    void two_fields(frame_width f_choice,
                    bay_width long_field,
                    bay_width short_field,
                    int number_Sfields);
};

#endif // SCAFF_H
