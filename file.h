#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include <cstdlib>

class file {
private:
	std::string file_name;
	std::list<std::string> content;
public:
	file(std::string name);
	void show_content(){
		for(auto i:content)
			std::cout << i.c_str() << '\n';
	}
	void delete_entry(std::string entry){content.remove(entry);}
	~file();

};

#endif // FILE_H
