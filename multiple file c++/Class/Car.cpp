#include "../Header.h"


class Car : public Vehicle{
public:
    void special(){
        std::cout << "This is a car\n";
    }
    void mySpecial(){
        std::cout<< "This is car my special\n";
    }
};