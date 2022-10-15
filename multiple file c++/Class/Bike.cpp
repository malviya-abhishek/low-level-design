#include "../Header.h"


class Bike : public Vehicle{
public:
     void special(){
        std::cout << "This is Bike new\n";
    }

    void mySpecial(){
        std::cout << "This is bike my special\n";
    }
};
