#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Road.hpp"
#include "Card.hpp"

namespace ariel {

class Land;  // Forward declaration
class Vertex; // Forward declaration
    class Player {

    private:
        std::string name;
        int points;
        int index;
        bool isHisTurn = false;
        bool firstRound=false;
        bool secondRound = false;
        int knightsCount =0;
        bool isGameOver = false;

        std::vector<ResourceCard> resourceCards;
        std::vector<DevelopmentCard> developmentCards;

    public:
        Player(std::string name, int index);
        void placeRoad(std::vector<std::string> places, std::vector<int> placesNum, std::vector<std::vector<Land*>>& lands);
        void placeSettelment(std::vector<std::string> places, std::vector<int> placesNum, std::vector<std::vector<Land*>>& lands);
        void placeCity(std::vector<std::string> places, std::vector<int> placesNum, std::vector<std::vector<Land*>>& lands);

        Road* checkAvilableRoads(Land* land);
        Vertex* checkAvilableVertex(Land* land);
        Vertex* checkForSettelment(Land* land);
        bool ownNeighborRoad(Vertex* v);
        bool isNeighborVertex(Vertex* v);

        void addResourceCard(Resource res);
        bool haveEnoughResource(std::vector<Resource> res);
        bool isResourceInResourceCard(Resource res);
        void deleteResources(std::vector<Resource>);
        int deleteResource(Resource resource);
        void claimResource(Vertex* v,vector<vector<Land*>>& lands);
        void cutResourceCards(vector<Player*>& players);
        void deleteDevelopmentCardByIndex(int index);
        int getResourceIndex(std::vector<ResourceCard>& resourceCard, Resource res);
        int getDevolopmentCardIndex(string typeCard);


        void addDevolpmentCard(DevelopmentCard devCard);
        void useMonopoleCard(vector<Player*>& players,Resource resourceToGet);
        void usePlentyYearCard(vector<Resource> resourceToGetfromBank,vector<Player*>& players);
        void useBuildingRoadsCard(vector<vector<Land*>>& lands,vector<Player*>& players);


        void handleDice(int diceOutcome , vector<vector<Land*>>& lands , vector<Player*>& players);
        void changeTurn(bool boolean);
        bool tradeResource(Player& player, Resource resource1 , Resource resource2);
        bool tradeDevolpmentCards(Player& player, DevelopmentCard devCard1 , DevelopmentCard devCard2,bool armyCard);
        int rollDice(vector<vector<Land*>>& lands , vector<Player*>& players);

        void endTurn(vector<Player*>& players);
        bool checkTurn();
        int getPoints();
        void addPoint();
        int getIndex();
        bool isPlayerWon();
        void printPoints();
        int getKnightsCount();
        void setIsGameOver();
        void decreasePoint();
        std::vector<ResourceCard>& getResourceCards();
        std::vector<DevelopmentCard>& getDevolopmentCards();


        std::string printPlayer() const;
    };
}


#endif // PLAYER_HPP
