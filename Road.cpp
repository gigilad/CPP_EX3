#include "Road.hpp"
#include <iostream>

namespace ariel {
    Road::Road(Vertex* Vertex1, Vertex* Vertex2) : firstVertex(Vertex1), secondVertex(Vertex2) {}

    void Road::printRoad() {
        std::cout << "first Vertex ";
        firstVertex->printVertex();
        std::cout << "second Vertex ";
        secondVertex->printVertex();
        std::cout << std::endl;
    }

    int Road::getRoadOwner() {
        return ownerIndex;
    }

    void Road::setRoadOwner(int playerIndex) {
        setOwner(playerIndex);
    }
    bool Road::operator==(Road& road){
        return (*this->getVertex1() == *road.getVertex1() && *this->getVertex2() == *road.getVertex2() ||
        *this->getVertex1() == *road.getVertex2() && *this->getVertex2() == *road.getVertex1());

    }

    Vertex* Road::getVertex1() {
        return firstVertex;
    }

    Vertex* Road::getVertex2() {
        return secondVertex;
    }
}
