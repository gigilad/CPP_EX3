#ifndef BOARD_HPP
#define BOARD_HPP
#include "Land.hpp"
#include <array>
#include "Building.hpp"
#include "Road.hpp"
#include <map>
using namespace std;

const int BOARD_SIZE = 19;
const int BOARD_LENGTH =5;
namespace ariel{
    class Vertex; // Forward declaration
    class Road;   // Forward declaration
    class Board {
    private:
        int boardLength = 5;
        vector<Vertex*> vertices;
        vector<Road*> roads;
        vector<vector<Land*>> hexagons;
        array<array<Building ,6>,11> buildings;

        void setBoard();
        void initLands();
        void initSettelments();
        Land* createLand(map<Resource,int>& resourceToInit,map<int,int>& numberOnLands,vector<Resource>& resources);
        bool areAllValuesZero(const map<Resource, int>& resourceMap);
        bool findKey(map<int,int>& map, int key);
        Vertex* getVertex(int i , int j);
        Road* getRoad(Vertex* start , Vertex* end);
    public:
        Board();
         vector<vector<Land*>>&getBoard() ; // no need
         array<array<Building ,6>,11>& getBuildings();
         vector<Vertex*>& getVertices();
         void printBoard();
    };



}

#endif