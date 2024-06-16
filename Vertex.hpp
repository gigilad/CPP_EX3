//gilada8892@gmail.com
#ifndef Vertex_HPP
#define Vertex_HPP
#include "Building.hpp"
#include "Road.hpp"
#include "Resource.hpp"
#include <vector>


using namespace std;
namespace ariel{
    class Road; // Forward declaration
    class Vertex : public Building{
        private:
        bool isCity=false;
        int x; // (x,y)
        int y; // (x,y)
        vector<Vertex*> neighborsVertices;
        vector<Road*> neighborRoads;
        vector<Resource> resources;

        public:
            Vertex(int x , int y);
            int getX();
            int getY();
            void addResource(Resource res);
            void printVertex();
            void addNeighborVertex(Vertex* vertex);
            void addNeighborRoad(Road* road);

            vector<Vertex*>& getNeighhborsVertices();
            vector<Road*>& getNeighborRoads();
            vector<Resource>& getResources();
            void setIsCity(bool bol);
            bool getisCity();

            bool operator==(Vertex& v2);
    };

}


#endif