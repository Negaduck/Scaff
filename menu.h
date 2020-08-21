#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

#include "DataBase.h"
#include "scaff.h"

template<typename Target,typename Source>
Target lexical_cast(Source arg);

void banner();
std::string new_facade();
void new_modul();
void delete_work();
void print_file(const char *file_name);
int main_menu();
int scaff_menu();
void my_remove(const char *rm);

#endif // MENU_H
