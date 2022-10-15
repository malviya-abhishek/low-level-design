#include "../Header.h"


class Vehicle{
public:
    int wheels;
    int doors;
    
    int getWheels(){
        return this->wheels;
    }

    int getDoors(){
        return this->doors;
    }

    void special(){
        std::cout << "This is Vehicel\n";
    }

    void mySpecial();
};