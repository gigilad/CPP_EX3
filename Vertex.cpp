//gilada8892@gmail.com
#include <iostream>
#include "Vertex.hpp"

using namespace std;

namespace ariel {
    Vertex::Vertex(int xCor, int yCor): x(xCor), y(yCor) {} // Initialize x and y cordinates

    void Vertex::setIsCity(bool bol){
        this->isCity = bol;
    }

    int Vertex::getX(){
        return x;
    }
    int Vertex::getY(){
        return y;
    }
    bool Vertex::getisCity(){
        return isCity;
    }
    vector<Resource>& Vertex::getResources(){
        return resources;
    }
    void Vertex::addResource(Resource r){
        if(resourceToString(r) != "DESERT"){
        resources.push_back(r);
        }


    }
    vector<Vertex*>& Vertex::getNeighhborsVertices(){
        return neighborsVertices;
    }

     vector<Road*>& Vertex::getNeighborRoads(){
        return neighborRoads;
     }

    void Vertex::addNeighborVertex(Vertex* vertex){
        // Check if the vertex is already in the neighborhood
        for (Vertex* neighbor : neighborsVertices) {
            if (*neighbor == *vertex) {
                return; // Vertex found in neighborhood, no need to add
            }
        }
        // Vertex not found, add it to the neighborhood
        neighborsVertices.push_back(vertex);
    }
    void Vertex::addNeighborRoad(Road* road){
        // Check if the vertex is already in the neighborhood
        for (Road* neighbor : neighborRoads) {
            if (*neighbor == *road) {
                return; // road found in neighborhood, no need to add
            }
        }
        // road not found, add it to the neighborhood
        neighborRoads.push_back(road);

    }


    void Vertex::printVertex(){
        cout << " x -> " << x << "y -> " << y << endl;
    }
    bool Vertex::operator==(Vertex& v2){
        return (this->x == v2.getX() && this->y == v2.getY());
    }
}
