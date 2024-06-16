//gilada8892@gmail.com

#include "Building.hpp"
#include <iostream>

namespace ariel {
    Building::Building() : ownerIndex(-1) {}

    // Constructor that sets the owner to the provided Player pointer
    Building::Building(int numIndex) : ownerIndex(numIndex) {}

    // Getter for the owner
    int Building::getOwner(){
        return ownerIndex;
    }

    // Setter for the owner
    void Building::setOwner(int num) {
        ownerIndex = num;
    }
}