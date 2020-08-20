#include <sstream>
#include <iostream>
#include <string>

template<typename Target>
Target lexical_cast(std::string& arg)
{
    std::stringstream interpreter;
    Target result;
    if(   !(interpreter << arg)
       || !(interpreter >> result)
       || !(interpreter >> std::ws).eof())
            return 0;
        return result;
}

int main(){
    std::string input("");
    std::cout << "Machen Sie eine Eingabe: ";
    std::getline(std::cin, input);
    std::cout << "Ihr eingabe: " << lexical_cast<double>(input) << std::endl;
}
