#include "scaff.h"

#include "umlaute.h"

scaff::scaff(input user_input):
    //determine the exact
    //weight of each component
    weight( { {{4.0,5.8,7.6,9.5,11.3},  //alu-planks
        {8.0,11.2,15.0,18.0,21.0},   //steel-planks
        {7.7,10.8,13.9,17.0,20.1}
    },  //wodden-planks
    {   {8.4,12.0,19.0},             //normal-frames
        {11.2,15.4,23.5}
    },           //wide-frames
    {2.2,3.0,3.8,4.6,6.6},       //guards
    {2.5,3.8,5.0,6.3,7.3},       //toe board
    {7.6,7.8,8.8,9.8},           //vertical-braces
    {3.0,4.0},                   //end-guard
    {21.0,24.5},                 //ladder entrance
    3.2
}),                       //base jack
material(), u_input(user_input),
bays(0),short_bays(0),floors(0),
bw( { bay_width::two_h,bay_width::three}),
fh(frame_height::normal),
fw(frame_width::thin) {
    if(u_input.load_class > 3)
        fw = frame_width::wide;
    set_floors();

}

scaff::~scaff() {}

void scaff::set_floors() {
    int rest_height;
    if(u_input.height % 200) {
        rest_height = u_input.height % 200;
        floors = u_input.height / 200;
        if(rest_height <= 50) {
            set_fields();
        } else if(rest_height >= 51 && rest_height <= 100) {
            floors+=1;
            fh = mini;
            set_fields();
        } else if(rest_height >= 101 && rest_height <= 150) {
            floors+=1;
            fh = frame_height::small;
            set_fields();
        } else if(rest_height >= 151) {
            floors+=1;
            fh = medium;
            set_fields();
        }
    } else {
        floors = u_input.height / 200;
        set_fields();
    }
}

double scaff::set_stalkload(bay_width bw, int floors) {
    double kg=0;
    kg += ((weight.guard[bw]*2)+weight.guard[bw]) *floors;
    kg += weight.t_board[bw] *floors;
    kg += (weight.dia[bw] *floors)/2;
    if(u_input.load_class < 4)
        kg += (weight.fchoice.frame[bw] *(floors+1))/2;
    else
        kg += (weight.fchoice.w_frame[bw] *(floors+1))/2;
    switch(u_input.load_class) {
    case 1:
        kg += weight.pchoice.alu[bw] * floors;
        break;
    case 2:
        kg += weight.pchoice.steel[bw] * floors;
        break;
    case 3:
        kg += weight.pchoice.wodden[bw] * floors;
        break;
    }
    return kg/100;
}

void scaff::set_fields() {
    if(u_input.plank_choice == 1) { //ALU
        if(u_input.load_class != 6) {
            long_fields();
        } else {
            short_fields();
        }
    } else if(u_input.plank_choice == 2) { //STEEL
        if(u_input.load_class < 5) {
            long_fields();
        } else {
            short_fields();
        }
    } else if(u_input.plank_choice == 3) { //WODDEN
        if(u_input.load_class < 4) {
            long_fields();
        } else {
            short_fields();
        }
    }
}

void scaff::short_fields() {
    int rest_lenght;
    bw[0] = bay_width::two_h;
    if(u_input.lenght % 250) {
        rest_lenght = u_input.lenght % 250;
        bays = u_input.lenght / 250;
        if(u_input.lenght <= 30) {
            set_frames();
            one_field(fw, two_h);
        } else if(rest_lenght >= 31 && rest_lenght <= 75) {
            bays += 1;

            short_bays =2;
            bw[0] = one_h;
            set_frames();
            two_fields(fw,two_h,one_h,2);
        } else if(rest_lenght >= 76 && rest_lenght <= 125) {
            bays+=1;
            short_bays =3;
            bw[0] = two;
            set_frames();
            two_fields(fw,two_h,two,3);
        } else if(rest_lenght >= 126 && rest_lenght <= 175) {
            bays+=1;
            short_bays =2;
            bw[0] = two;
            set_frames();
            two_fields(fw,two_h,two,2);
        } else if(rest_lenght >= 176 && rest_lenght <= 225) {
            bays+=1;
            short_bays =1;
            bw[0] = two;
            set_frames();
            two_fields(fw,two_h,two,1);
        } else if(rest_lenght >= 226) {
            bays+=1;
            set_frames();
            one_field(fw,two_h);
        }
    } else {
        bays = u_input.lenght / 250;
        set_frames();
        one_field(fw,two_h);
    }
}

void scaff::long_fields() {
    int rest_lenght;
    if(u_input.lenght % 300) {
        rest_lenght = u_input.lenght % 300;
        bays = u_input.lenght / 300;
        if(rest_lenght <= 30) {
            set_frames();
            one_field(fw,three);
        } else if(rest_lenght >= 31 && rest_lenght <= 75) {
            bays += 1;
            if(bays > 5) {
                short_bays = 5;
                two_fields(fw, three, two_h, 5 );
                set_frames();
            } else {
                set_frames();
                short_bays = 1;
                bw[0] = one;
                two_fields(fw,three,one,1);
            }
        } else if(rest_lenght >= 76 && rest_lenght <= 125) {
            bays += 1;
            if(bays > 4) {
                set_frames();
                short_bays = 4;
                two_fields(fw, three, two_h, 4 );
            } else {
                set_frames();
                short_bays = 1;
                bw[0] = one;
                two_fields(fw,three, one, 1 );
            }
        } else if(rest_lenght >= 126 && rest_lenght <= 175) {
            bays += 1;
            if(bays > 3) {
                set_frames();

                short_bays = 3;
                two_fields(fw, three, two_h, 3 );
            } else {
                set_frames();
                short_bays = 1;
                bw[0] = one_h;
                two_fields(fw, three, one_h,1);
            }
        } else if(rest_lenght >= 176 && rest_lenght <= 225) {
            bays +=1;
            if(bays > 2) {
                set_frames();
                short_bays = 2;
                two_fields(fw, three, two_h, 2);
            } else {
                set_frames();
                short_bays = 1;
                bw[0] = two;
                two_fields(fw, three, two, 1 );
            }
        } else if(rest_lenght >= 226 && rest_lenght <= 275) {
            bays +=1;
            set_frames();
            short_bays = 1;
            two_fields(fw, three, two_h, 1);
        } else if( rest_lenght >= 276) {
            bays +=1 ;
            set_frames();
            one_field(fw, three );
        } else {
            bays = u_input.lenght / 300;
            if( u_input.load_class < 4) {
                set_frames();
                one_field(fw, three);
            } else {
                set_frames();
                one_field(fw,three);
            }
        }
    }
}

void scaff::one_field( frame_width f_choice, bay_width b_choice) {
    switch(u_input.plank_choice) {
    case 1:
        material.pchoice.alu[b_choice]   = ( ( bays * floors ) * f_choice )-( floors * 2);
        break;
    case 2:
        material.pchoice.steel[b_choice]   = ( ( bays * floors ) * f_choice )-( floors * 2);
        break;
    case 3:
        material.pchoice.wodden[b_choice]   = ( ( bays * floors ) * f_choice )-( floors * 2);
        break;
    }
    material.guard[b_choice]   = ( bays * 2 * floors) + bays;
    material.t_board[b_choice] = floors * bays;
    material.b_jack  = (bays + 1) * 2;
    if(u_input.load_class < 4 ) {
        material.e_guard[0] = floors*2;
    } else {
        material.e_guard[1] = floors*2;
    }
    material.ladder[1]    = floors;
    material.dia[b_choice] = ( (int)( bays / 5)+1)* floors ;
    set_stamp();
}

void scaff::two_fields( frame_width f_choice,
                        bay_width long_field,
                        bay_width short_field,
                        int number_Sfields) {
    switch(u_input.plank_choice) {
    case 1:
        material.pchoice.alu[long_field]   = (( bays * floors)*f_choice) -((floors*2)+((floors*f_choice)*number_Sfields));
        material.pchoice.alu[short_field]   = (floors * f_choice) * number_Sfields;
        break;
    case 2:
        material.pchoice.steel[long_field]   = (( bays * floors)*f_choice) -((floors*2)+((floors*f_choice)*number_Sfields));
        material.pchoice.steel[short_field]   = (floors * f_choice) * number_Sfields;
        break;
    case 3:
        material.pchoice.wodden[long_field]   = (( bays * floors)*f_choice) -((floors*2)+((floors*f_choice)*number_Sfields));
        material.pchoice.wodden[short_field]   = (floors * f_choice) * number_Sfields;
        break;
    }
    material.dia[long_field] = ( (int)( bays / 5)+1)* floors;
    if(bays <= 5)
        material.dia[long_field] = floors;
    material.guard[long_field]     = ((bays*2*floors)+bays)-(((floors*2)+1) * number_Sfields);
    material.guard[short_field]    = (2*floors+1)* number_Sfields;
    material.t_board[long_field]  = (floors * bays) - ( floors * number_Sfields);
    material.t_board[short_field] = floors * number_Sfields;
    material.b_jack 		 = (bays+1)*2;
    material.ladder[1]      		 = floors;
    if(u_input.load_class < 4 ) {
        material.e_guard[0] = floors*2;
    } else {
        material.e_guard[1] = floors*2;
    }
    set_stamp();
}

void scaff::set_frames() {
    if(fw == thin) {
        if(fh == normal)
            material.fchoice.frame[3] = (bays+1)*(floors+1);
        else {
            material.fchoice.frame[3] = (bays+1)*(floors+1) - (bays+1);
            material.fchoice.frame[fh] = bays+1;
        }
    } else {
        if(fh == normal)
            material.fchoice.frame[3] = (bays+1)*(floors+1);
        else {
            material.fchoice.frame[3] = (bays+1)*(floors+1) - (bays+1);
            material.fchoice.frame[fh] = bays+1;
        }
    }
}

double scaff::set_weight(components<int>& lhs, components<double>& rhs) {
    double weight = 0;
    weight =  lhs.dia[3] * rhs.dia[3] ;
    weight += lhs.e_guard[0] * rhs.e_guard[0] + lhs.e_guard[1] * rhs.e_guard[1];
    weight += lhs.ladder[1] * rhs.ladder[1];
    weight += lhs.b_jack * rhs.b_jack;
    weight += lhs.pchoice.alu[0] * rhs.pchoice.alu[0] + lhs.pchoice.alu[1] * rhs.pchoice.alu[1] +
              lhs.pchoice.alu[2] * rhs.pchoice.alu[2] + lhs.pchoice.alu[3] * rhs.pchoice.alu[3] +
              lhs.pchoice.alu[4] * rhs.pchoice.alu[4];
    weight += lhs.pchoice.steel[0] * rhs.pchoice.steel[0] + lhs.pchoice.steel[1] * rhs.pchoice.steel[1] +
              lhs.pchoice.steel[2] * rhs.pchoice.steel[2] + lhs.pchoice.steel[3] * rhs.pchoice.steel[3] +
              lhs.pchoice.steel[4] * rhs.pchoice.steel[4];
    weight += lhs.pchoice.wodden[0] * rhs.pchoice.wodden[0] + lhs.pchoice.wodden[1] * rhs.pchoice.wodden[1] +
              lhs.pchoice.wodden[2] * rhs.pchoice.wodden[2] + lhs.pchoice.wodden[3] * rhs.pchoice.wodden[3] +
              lhs.pchoice.wodden[4] * rhs.pchoice.wodden[4];
    weight += lhs.guard[0] * rhs.guard[0] + lhs.guard[1] * rhs.guard[1] +
              lhs.guard[2] * rhs.guard[2] + lhs.guard[3] * rhs.guard[3] +
              lhs.guard[4] * rhs.guard[4];
    weight += lhs.t_board[0] * rhs.t_board[0] + lhs.t_board[1] * rhs.t_board[1] +
              lhs.t_board[2] * rhs.t_board[2] + lhs.t_board[3] * rhs.t_board[3] +
              lhs.t_board[4] * rhs.t_board[4];
    weight += lhs.fchoice.frame[0] * rhs.fchoice.frame[0] + lhs.fchoice.frame[1] * rhs.fchoice.frame[1] +
              lhs.fchoice.frame[2] * rhs.fchoice.frame[2] + lhs.fchoice.frame[3] * rhs.fchoice.frame[3];
    weight += lhs.fchoice.w_frame[0] * rhs.fchoice.w_frame[0] + lhs.fchoice.w_frame[1] * rhs.fchoice.w_frame[1] +
              lhs.fchoice.w_frame[2] * rhs.fchoice.w_frame[2] + lhs.fchoice.w_frame[3] * rhs.fchoice.w_frame[3];
    return weight;

}

void scaff::set_stamp() {
    append_data(u_input.name.c_str());
    u_input.name += ".data";
    FILE* file=fopen(u_input.name.c_str(), "w+");
    fprintf(file,"\n\t\t\tMaterialliste\n");
    fprintf(file,"\n\t\t70er\t100er\n\n");
    fprintf(file,"Endschutz  \t %d\t %d\n",material.e_guard[0],material.e_guard[1]);
    fprintf(file,"50er Rahmen\t %d\t %d\n",material.fchoice.frame[0],material.fchoice.w_frame[0]);
    fprintf(file,"1.0m Rahmen\t %d\t %d\n",material.fchoice.frame[1],material.fchoice.w_frame[1]);
    fprintf(file,"1.5m Rahmen\t %d\t %d\n",material.fchoice.frame[2],material.fchoice.w_frame[2]);
    fprintf(file,"2.0m Rahmen\t %d\t %d\n\n",material.fchoice.frame[3],material.fchoice.w_frame[3]);
    fprintf(file,"\n        \t3m\t2.5m\t2m\t1.5m\t1m\n\n");
    fprintf(file,"Alu           \t%d\t%d\t%d\t%d\t%d\n",
            material.pchoice.alu[4],
            material.pchoice.alu[3],
            material.pchoice.alu[2],
            material.pchoice.alu[1],
            material.pchoice.alu[0]);
    fprintf(file,"Stahl         \t%d\t%d\t%d\t%d\t%d\n",
            material.pchoice.steel[4],
            material.pchoice.steel[3],
            material.pchoice.steel[2],
            material.pchoice.steel[1],
            material.pchoice.steel[0]);
    fprintf(file,"Holz          \t%d\t%d\t%d\t%d\t%d\n",
            material.pchoice.wodden[4],
            material.pchoice.wodden[3],
            material.pchoice.wodden[2],
            material.pchoice.wodden[1],
            material.pchoice.wodden[0]);
    fprintf(file,"\n\n        \t3m\t2.5m\t2m\t1.5m\t1m\n\n");
    fprintf(file,"Lehnen         \t%d\t%d\t%d\t%d\t%d\n",
            material.guard[4],material.guard[3],
            material.guard[2],material.guard[1],
            material.guard[0]);
    fprintf(file,"Bordbretter    \t%d\t%d\t%d\t%d\t%d\n",
            material.t_board[4],material.t_board[3],
            material.t_board[2],material.t_board[1],
            material.t_board[0]);
    fprintf(file,"Diagonalen    \t%d\t%d\t%d\t%d\t%d\n\n",
            material.dia[4],material.dia[3],
            material.dia[2],material.dia[1],
            material.dia[0]);
    fprintf(file,"\nDurchtiege\t %d\tAnker        \t %d\tKupplungen\t %d\n",material.ladder[1],(int)((bays*floors) /2.5),(int)((bays*floors) /2.5));
    fprintf(file,"F%csse      \t %d\tRingschrauben\t %d\tUnterlagen\t %d\n\n",ue,material.b_jack, (int)((bays*floors) /2.5),material.b_jack);
    first_print(file);
    fprintf(file,"\nEckdaten:\n");
    fprintf(file,"\nLange Felder: %d\t\tGewicht: %.2ft\nKurze Felder: %d\t\tStiellast: ca. %.2f kN\nLagen : %d",
            bays-short_bays, float(set_weight(material,weight)/1000),short_bays, set_stalkload(bw[1],floors), floors);
    fclose(file);
}

void scaff::append_data(const char *data) {
    FILE* file=fopen("c_siter.ger", "a");
    if(file == NULL) {
        printf("Dateifehler...\n");
        exit(0);
    }
    fprintf(file,"%s\n",data);
    fclose(file);
}

void scaff::first_print(FILE* file) {
    for(int i=1; i<=bays; i++) {
        fprintf(file," ___");
        if(i == bays)
            fprintf(file,"\n");
    }
    second_print(file);
}

void scaff::second_print(FILE* file) {
    for(int k=1; k<=floors; k++)
        for(int j=1; j<=bays; j++) {
            fprintf(file,"|___");
            if(j==bays)
                fprintf(file,"|\n");
        }
    fprintf(file,"\n");
}
