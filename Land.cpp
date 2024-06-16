#include "Land.hpp"
#include <iostream>
using namespace std;

namespace ariel
{
    Land::Land(Resource res, int number)
        : num(number), resourceType(res) {} // Initialize num first, then resource

    bool Land::isContainVertex(Vertex *v)
    {
        for (Vertex *vertex : vertices)
        {
            if (vertex == v)
            {
                return true;
            }
        }
        return false;
    }
    // Setters
    void Land::setNum(int number)
    {
        num = number;
    }

    void Land::addVertex(Vertex *v)
    {
        vertices.push_back(v);
    }
    void Land::addRoad(Road *r)
    {
        // 2 vertices of road are close;
        Vertex *v1 = r->getVertex1();
        Vertex *v2 = r->getVertex2();
        v1->addNeighborVertex(v2);
        v2->addNeighborVertex(v1);

        v1->addNeighborRoad(r);
        v2->addNeighborRoad(r);
        roads.push_back(r);
    }

    void Land::setResource(Resource res)
    {
        resourceType = res;
    }

    // Getters
    int Land::getNum()
    {
        return num;
    }

    Resource Land::getResource()
    {
        return resourceType;
    }
    std::vector<Road *> &Land::getRoads()
    {
        return roads;
    }
    std::vector<Vertex *> &Land::getVertices()
    {
        return vertices;
    }
    // Display the land
    void Land::display()
    {
        cout << "Resource " << resourceToString(resourceType) << ", num " << num << endl;
        cout << " i have vertices " << vertices.size() << " and roads " << roads.size() << endl;
    }
}
