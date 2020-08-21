#include "menu.h"
#include "version.h"
#include "modul_scaff.h"
#include <sstream>


//Little debug function
//that just prints the given 
//parameter T
template<typename T>
void DEBUG(T OutVal){
	std::cerr << OutVal << std::endl;
}


//Converts the Input type into the
//return value type examples
template<typename Target,typename Source>
Target lexical_cast(Source arg)
{
    std::stringstream interpreter;
    Target result;
    if(   !(interpreter << arg)
       || !(interpreter >> result)
       || !(interpreter >> std::ws).eof())
            return 0;
        return result;
}


void print_file(const char *file_name){
	std::ifstream f(file_name);
	if(f.good()){
		std::string s;
	    while (!f.eof()){
	   		getline(f, s);
	   		std::cout << s << std::endl;
	   	}
	    f.close();
	}
}

int main_menu(){
	int choice=0;
	std::string temp("");
	banner();
	std::cout << "\n\n\t[1] Fassadenger"<< ue << "st\n";
	std::cout << "\t[2] Modulger"<< ue << "st\n";
	std::cout << "\t[3] Beenden\n\n";
	std::cout << "Ihre Auswahl: ";
	std::getline(std::cin,temp);
	choice = lexical_cast<int,std::string>(temp);
	return choice;
}

int scaff_menu(){
	#ifdef _WIN32
			system("cls");
		#else 
			system("clear");
		#endif
	int choice=0;
	std::string temp("");
	banner();
	std::cout << "\n\n\t[1] Aufbau\n";
	std::cout << "\t[2] Abbau\n\n";
	std::cout << "Ihre Auswahl: ";
	std::getline(std::cin,temp);
	choice = lexical_cast<int,std::string>(temp);
	return choice;
}

void banner(){
	std::cout << "\t************  *****   *****   ***********    ******   *****" << std::endl;
    std::cout << "\t*   ********  *   *   *   *   *  .....  *    *    *  *   *" << std::endl;
	std::cout << "\t*   *         *   *   *   *   *  :...:  *    *    * *   *" <<std::endl;
    std::cout << "\t*   *         *   *****   *   *         *    *    **   *" <<std::endl;
	std::cout << "\t*   ****      *           *   *   *****      *    *   *" << std::endl;
	std::cout << "\t*   ****      *   *****   *   *  .....  *    *       *" << std::endl;
	std::cout << "\t*   *         *   *   *   *   *  :...:  *    *         *" <<std::endl;
	std::cout << "\t*   *         *   *   *   *   *         *    *     **   *"  <<std::endl;
    std::cout << "\t*****         *****   *****   ***********    ******  *****" <<std::endl;
}

void my_remove(const char *rm) {
   unsigned long size;
   FILE *rem=fopen(rm, "w+b");
   if(rem != NULL)  {
      fseek(rem, 0L, SEEK_END);
      size=ftell(rem);
      fwrite((char *)'\0', 1, size, rem);
      fclose(rem);
      remove(rm);
   }
}

void delete_work(){
	#ifdef _WIN32
			system("cls");
		#else 
			system("clear");
		#endif
	DataBase f("c_siter.ger");
	banner();
	f.show_content();
	std::string del_name;
	std::cout << "\nGeben Sie die Baustelle ein: ";
	std::cin >> del_name;
	f.delete_entry(del_name);
	del_name += ".data";
	print_file(del_name.c_str());
	my_remove(del_name.c_str());
}

void new_modul(){
	m_input user_input;
	std::string temp;
	double h;
	std::cout << "Arbeitslage: ";
	std::getline(std::cin,temp);
	h = lexical_cast<double,std::string>(temp);
	user_input.height = (h *= 100);
	std::cout << "Laenge: ";
	std::getline(std::cin,temp);
	h = lexical_cast<double,std::string>(temp);
	user_input.length = (h *= 100);
	std::cout << "Breite: ";
	std::getline(std::cin,temp);
	h = lexical_cast<double,std::string>(temp);
	user_input.width = (h *= 100);
	std::cout << "Lastklasse: ";
	std::getline(std::cin,temp);
	user_input.load_class = lexical_cast<int,std::string>(temp);
	modul_scaff mscaff(user_input);

}

void new_facade(){
	input FacadeInput;
	GetUserInput(FacadeInput);
    scaff scaff1(FacadeInput);
	scaff1.print_data(stdout);
	int choice=0;
	std::cout << "\n1Wollen Sie die Daten speichern?\n";
	std::cin>>choice;
	switch(choice){
		case 1:
			scaff1.save_data();
			break;
		default:
			exit(0);
	}

}

int GetUserInput(input &User){
		#ifdef _WIN32
			system("cls");
		#else 
			system("clear");
		#endif
		// From here we interact with the 
		//user and try to get all the needed
		// data to calculate components
		//input User;
		banner();
		std::cout << "\n\n\t\t\tAnforderungen\n\n";
		std::cout << "\tBaustellenname: ";
        std::cin.sync();
		std::getline(std::cin,User.name);
		std::cout << "\n\tBevorzugte Bohlen\n\t<1> Alubohlen\n"
					 "\t<2> Stahlbohlen\n\t<3> Holzbohlen\n";
		std::cout << "\tIhre Wahl: ";
		std::cin >> User.plank_choice;
		std::cout << "\tLastklasse: ";
		std::cin >> User.load_class ;
		if( User.load_class <= 0 || User.load_class > 6) {
			std::cout <<"*****************************************\n";
			std::cout << "Falsche Eingabe\t\t\t\t*\nLastklasse zwischen 1 und 6\t\t*\n";
			std::cout <<"*****************************************\n";
			std::cout << "\tLastklasse: ";
			std::cin >>  User.load_class;
		}
		if((User.load_class == 5 || User.load_class == 6) && User.plank_choice == 3) {
			std::cout << "Unwirtschaftlich...\nVerwenden Sie Alu-oder Stahlbohlen!!!\n";
			exit(0);
		}
		if( User.load_class == 6 && User.plank_choice == 2) {
			std::cout << "Unwirtschaftlich...\nVerwenden Sie Alubohlen!!!\n";
			exit(0);
		}
		double lang, hoch;
		std::string conv;
		std::cout << "\tHoehe: ";
		std::cin.sync();
		std::cin >> hoch;
		//std::getline(std::cin, conv);
		//hoch = lexical_cast<double, std::string>(conv);
		User.height = (hoch *=100);
		std::cout << "\tLaenge: ";
		std::cin.sync();
		std::cin >> lang;
		//std::getline(std::cin, conv);
		//lang = lexical_cast<double, std::string>(conv);
		User.lenght = lang *=100;
		//Now we get all the Data we need
		//
		//Here starts the actual heart of the program to beat
		//We can create a Scaff object to compute material
		//scaff scaff1(User);
		User.name += ".data";
		return 0;
}

int add_entry(const char *new_entry){
	FILE* file=fopen("c_siter.ger", "a");
    if(file == NULL) {
        printf("Dateifehler...\n");
        return 1;
    }
    fprintf(file,"%s\n",new_entry);
    fclose(file);
	return 0;
}
