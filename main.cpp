#include <iostream>

#include "scaff.h"
#include "file.h"
#include "menu.h"

int main() {
    switch(main_menu()) {
    case 1:
        switch(scaff_menu()) {
        case 1:
            print_file(new_facade().c_str());
            break;
        case 2:
            delete_work();
            break;
        }
        break;
    case 2: new_modul();
            break;

    }
    return 0;
}
