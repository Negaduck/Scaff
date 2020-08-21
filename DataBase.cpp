#include "DataBase.h"

DataBase::DataBase(std::string name):file_name(name),
							 		content(){
	std::ifstream file(file_name);
	/*if(file == NULL){
		std::cout << "Dateifehler...";
		exit(0);
	}*/
	std::string temp;
	while(file >> temp) content.push_back(temp);
	file.close();
}

DataBase::~DataBase() {
	FILE* file = fopen("c_siter.ger","w+");
	for(auto i : content ){
		fprintf(file,"%s\n", i.c_str());
	}
	fclose(file);
}


void DataBase::show_content(){
		if(content.size() == 0){		//Maybe there are no saved Names in the file
			std::cout << "Es sind keine Bauvorhaben vorhanden...\n";
			exit(1);
		}
		for(auto i:content)
			std::cout << i.c_str() << '\n';
	}
