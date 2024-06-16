#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <string>
using namespace std;

namespace ariel {
    class Building {
    protected:
        int ownerIndex = -1;

    public:
        Building();
        Building(int index);
        virtual int getOwner();
        virtual void setOwner(int index);

    };
}

#endif // BUILDING_HPP
