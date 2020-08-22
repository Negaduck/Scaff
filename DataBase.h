#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include <cstdlib>

//
//This is our small internally database
//For every new Construction Site the User
//adds, we take the construction name 
//append += .data and save this in a file
// called c_siter.ger
//
class DataBase {
private:
	std::string file_name;
	std::list<std::string> content;
public:
	//Read in all Names(Construction sites)
	//we saved in "c_siter.ger"
	DataBase(std::string name);
	void show_content();
	void delete_entry(std::string entry){content.remove(entry);}
	void add_entry(const char *new_entry);
	~DataBase();
};

#endif // DATABASE
