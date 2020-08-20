#include "file.h"

file::file(std::string name):file_name(name),
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

file::~file() {
	FILE* file= fopen("c_siter.ger","w+");
	for(auto i : content ){
		fprintf(file,"%s\n", i.c_str());
	}
	fclose(file);
}
