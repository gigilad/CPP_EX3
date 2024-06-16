//gilada8892@gmail.com

#include "Board.hpp"
#include <iostream>
#include <map>
#include <ctime>
#include <vector>
using namespace std;
namespace ariel
{
    Board::Board() : hexagons(boardLength, vector<Land *>(boardLength, nullptr))
    {
        setBoard();
    }

    void Board::initLands()
    {
        srand(std::time(0));
        vector<Resource> resources = {
            Resource::WOOD,
            Resource::BRICK,
            Resource::WOOL,
            Resource::OATS,
            Resource::IRON,
            Resource::DESERT};
        map<Resource, int> resourceToInit = {
            {Resource::WOOD, 4},
            {Resource::BRICK, 3},
            {Resource::WOOL, 4},
            {Resource::OATS, 4},
            {Resource::IRON, 3},
            {Resource::DESERT, 1}};
        // whice number and how many of it we want to put on the lands
        map<int, int> numberOnLands = {
            {2, 1},
            {3, 2},
            {4, 2},
            {5, 2},
            {6, 2},
            {8, 2},
            {9, 2},
            {10, 2},
            {11, 2},
            {12, 1}};

        for (int i = 0; i < boardLength; i++)
        {
            for (int j = 0; j < boardLength; j++)
            {
                if (i + j >= 2 && i + j <= boardLength + 1)
                {
                    // create a pointer to hexygon
                    Land *land = createLand(resourceToInit, numberOnLands, resources);
                    int rowIndex = (2 * (i - 1)) + j;
                    int colIndex = j;
                    // get all 6 vertices of the hexygon;
                    Vertex *v1 = getVertex(rowIndex, colIndex);
                    Vertex *v2 = getVertex(rowIndex + 1, colIndex);
                    Vertex *v3 = getVertex(rowIndex + 2, colIndex);
                    Vertex *v4 = getVertex(rowIndex + 2, colIndex + 1);
                    Vertex *v5 = getVertex(rowIndex + 1, colIndex + 1);
                    Vertex *v6 = getVertex(rowIndex, colIndex + 1);

                    v1->addResource(land->getResource());
                    v2->addResource(land->getResource());
                    v3->addResource(land->getResource());
                    v4->addResource(land->getResource());
                    v5->addResource(land->getResource());
                    v6->addResource(land->getResource());

                    land->addVertex(v1);
                    land->addVertex(v2);
                    land->addVertex(v3);
                    land->addVertex(v4);
                    land->addVertex(v5);
                    land->addVertex(v6);

                    // get all 6 roads
                    Road *r1 = getRoad(v1, v2);
                    Road *r2 = getRoad(v2, v3);
                    Road *r3 = getRoad(v3, v4);
                    Road *r4 = getRoad(v4, v5);
                    Road *r5 = getRoad(v5, v6);
                    Road *r6 = getRoad(v6, v1);

                    land->addRoad(r1);
                    land->addRoad(r2);
                    land->addRoad(r3);
                    land->addRoad(r4);
                    land->addRoad(r5);
                    land->addRoad(r6);

                    hexagons[i][j] = land;
                }
            }
        }
    }

    Land *Board::createLand(map<Resource, int> &resourceToInit, map<int, int> &numberOnLands, vector<Resource> &resources)
    {
        //     for (const auto& pair : resourceToInit) {
        //     std::cout << "Resource: " << static_cast<int>(pair.first) << ", Initialization: " << pair.second << std::endl;
        // }

        if (areAllValuesZero(resourceToInit) || resourceToInit.empty() || numberOnLands.empty() || resources.empty())
        {
            throw new invalid_argument("empty map");
        }

        int lowIndex = 1;
        int highIndex = resourceToInit.size();

        // Generate a random number between 1 and resourceToInit.size()
        int randomIndex;
        randomIndex = rand() % highIndex + lowIndex;

        Resource selectedResource = resources[randomIndex - 1];
        resourceToInit[selectedResource]--;

        if (resourceToInit[selectedResource] == 0)
        {
            resourceToInit.erase(selectedResource);
            resources.erase(resources.begin() + randomIndex - 1);
        }

        if (selectedResource == Resource::DESERT)
        {
            return new Land(selectedResource, 0);
        }

        int keyIndex;
        keyIndex = rand() % (12 - 2 + 1) + 2;
        do
        {
            keyIndex = rand() % (12 - 2 + 1) + 2;
        } while (!findKey(numberOnLands, keyIndex));

        numberOnLands[keyIndex]--;

        if (numberOnLands[keyIndex] == 0)
        {
            numberOnLands.erase(keyIndex);
        }

        return new Land(selectedResource, keyIndex);
    }

    void Board::initSettelments()
    {
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (i + j >= 2 && i + j <= 13 && j - i <= 3 && j - i >= -8)
                {
                    // deafualt constractur make this settlement to have nullPtr owner
                    buildings[i][j] = Building();
                }
            }
        }
    }

    // setters
    void Board::setBoard()
    {
        initSettelments();
        initLands();
    }
    // getters
    Vertex *Board::getVertex(int i, int j)
    {
        for (auto vertex : vertices)
        {
            // checking if vertex already in created
            if (vertex->getX() == i && vertex->getY() == j)
            {
                return vertex;
            }
        }
        Vertex *newVertex = new Vertex(i, j);
        vertices.push_back(newVertex);
        return newVertex;
    }

    Road *Board::getRoad(Vertex *start, Vertex *end)
    {
        for (auto road : roads)
        {
            if ((road->getVertex1() == start && road->getVertex2() == end) ||
                road->getVertex1() == end && road->getVertex2() == start)
            {
                return road;
            }
        }
        Road *newRoad = new Road(start, end);
        roads.push_back(newRoad);
        return newRoad;
    }

    vector<Vertex *> &Board::getVertices()
    {
        return vertices;
    }
    vector<vector<Land *>> &Board::getBoard()
    {
        return hexagons;
    }
    array<array<Building, 6>, 11> &Board::getBuildings()
    {
        return buildings;
    }
    // helpers
    void Board::printBoard()
    {
        for (auto &row : hexagons)
        {
            for (auto &land : row)
            {
                if (land != nullptr)
                {
                    std::cout << "[ " << resourceToString(land->getResource()) << "  " << land->getNum() << "]";
                }
                else
                {
                    std::cout << " [ ] ";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
    bool Board::findKey(map<int, int> &map, int key)
    {
        if (map.find(key) != map.end())
        {
            return true;
        }
        return false;
    }
    bool Board::areAllValuesZero(const map<Resource, int> &resourceMap)
    {
        for (const auto &pair : resourceMap)
        {
            if (pair.second != 0)
            {

                return false;
            }
        }
        return true;
    }
}