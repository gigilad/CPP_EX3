#ifndef LAND_HPP
#define LAND_HPP
#include "Resource.hpp"
#include <vector>
#include "Road.hpp"


namespace ariel {

    class Road;   // Forward declaration
    class Vertex; // Forward declaration

    class Land {
    private:
        int num;
        Resource resourceType;
        std::vector<Road*> roads;
        std::vector<Vertex*> vertices;
    public:
        Land(Resource resourceType = Resource::NONE, int num = 0);
        void addVertex(Vertex* v);
        void addRoad(Road* v);
        std::vector<Road*>& getRoads();
        std::vector<Vertex*>& getVertices();
        int getNum();
        Resource getResource();
        void setNum(int num);
        void setResource(Resource resource);
        void display();
        bool isContainVertex(Vertex* v);
    };
}

#endif
