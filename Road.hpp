//gilada8892@gmail.com
#ifndef ROAD_HPP
#define ROAD_HPP

#include "Building.hpp"
#include "Vertex.hpp" // Assuming you need Vertex, make sure it's included
#include <string>
class Building;

namespace ariel {
    class Vertex;
    class Road : public Building {
    private:
        int indexOwner = -1;
        Vertex* firstVertex;  // (x,y)
        Vertex* secondVertex; // (x,y)

    public:
        Road(Vertex* Vertex1, Vertex* Vertex2);
        void printRoad();
        Vertex* getVertex1();
        Vertex* getVertex2();
        void setRoadOwner(int index);
        int getRoadOwner();

        bool operator==(Road& road);
    };
}

#endif // ROAD_HPP
