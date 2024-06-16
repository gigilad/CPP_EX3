#include "Player.hpp"
#include "Land.hpp"
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;
namespace ariel
{
    Player::Player(string name, int index) : name(name), points(0), index(index) {}

    void Player::placeCity(std::vector<std::string> places, std::vector<int> placesNum, std::vector<std::vector<Land *>> &lands)
    {
     if(isGameOver){
           throw runtime_error("Game is over");
           return;
        }
        if (!checkTurn())
        {
            throw runtime_error("it is not tour turn (in place city)!");
            return;
        }
        for (auto &row : lands)
        {
            for (Land *land : row)
            {
                if (land != nullptr)
                {
                    bool numFound = find(placesNum.begin(), placesNum.end(), land->getNum()) != placesNum.end();
                    bool resourceFound = find(places.begin(), places.end(), resourceToString(land->getResource())) != places.end();
                    if (numFound && resourceFound)
                    {
                        Vertex *vex = checkForSettelment(land);
                        if (vex != nullptr)
                        {
                            //Need to check if the player have the resources;
                            std::vector<Resource> resourcesForCity = {Resource::IRON, Resource::IRON, Resource::IRON, Resource::OATS, Resource::OATS};
                            if (haveEnoughResource(resourcesForCity))
                            {
                                vex->setIsCity(true);
                                this->addPoint();
                                deleteResources(resourcesForCity);
                                std::cout << "now vertex is a city and have index of player " << vex->getOwner()+1 << std::endl;
                                return;
                            }
                            else
                            {
                                throw runtime_error("You dont have enough resources to place city");
                                return;
                            }
                        }

                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }

    void Player::placeSettelment(vector<string> places, vector<int> placesNum, vector<vector<Land *>> &lands)
    {
         if(isGameOver){
           throw runtime_error("Game is over");
           return;
        }
        if (!(checkTurn()))
        {
            throw runtime_error("it is not tour turn (in place settlement)!");
            return;
        }
        for (auto &row : lands)
        {
            for (Land *land : row)
            {
                if (land != nullptr)
                {
                    bool numFound = find(placesNum.begin(), placesNum.end(), land->getNum()) != placesNum.end();
                    bool resourceFound = find(places.begin(), places.end(), resourceToString(land->getResource())) != places.end();
                    if (numFound && resourceFound)
                    {
                        Vertex *vex = checkAvilableVertex(land);
                        if (vex != nullptr)
                        {
                            // if its first or second round we will serach for resource for the resourceCard
                            if (!this->secondRound || !this->firstRound)
                            {
                                claimResource(vex, lands);
                                vex->setOwner(index);
                                std::cout << "Placed settelment in "<<land->getNum() <<" with Resource "<< resourceToString(land->getResource()) <<std::endl;
                                this->addPoint();
                                if (!this->firstRound)
                                {
                                    this->firstRound = true;
                                }
                                else
                                {
                                    this->secondRound = true;
                                }
                            }
                            else
                            {
                                // if it not the first and second round -need to check if he have enough resources;
                                std::vector<Resource> resources = {Resource::BRICK, Resource::WOOD, Resource::WOOL, Resource::OATS};
                                if (haveEnoughResource(resources))
                                {
                                    vex->setOwner(index);
                                    this->addPoint();
                                    deleteResources(resources);
                                }
                                else
                                {
                                    std::cout << "You dont have enough resources to place seetlement" << std::endl;
                                }
                            }

                            std::cout << "now player " << vex->getOwner()+1<< " owns this vertex " << std::endl;
                            return;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
        std::cout << "didnt found ligal place for settelement " << std::endl;

    }

    void Player::placeRoad(vector<string> places, vector<int> placesNum, vector<vector<Land *>> &lands)
    {
        if(isGameOver){
           throw runtime_error("Game is over");
           return;
        }
        if (!(checkTurn()))
        {
            std::cout << "it is not tour turn!(place road)" << std::endl;
            return;
        }
        // we give priority to the numbers we got and the places;
        for (auto &row : lands)
        {
            for (Land *land : row)
            {
                if (land != nullptr)
                {
                    bool numFound = find(placesNum.begin(), placesNum.end(), land->getNum()) != placesNum.end();
                    bool resourceFound = find(places.begin(), places.end(), resourceToString(land->getResource())) != places.end();
                    if (numFound && resourceFound)
                    {
                        Road *road = checkAvilableRoads(land);
                        // we found Road
                        if (road != nullptr)
                        {
                            if (firstRound && secondRound)
                            {
                                std::vector<Resource> resources = {Resource::BRICK, Resource::WOOD};
                                if (haveEnoughResource(resources))
                                {
                                    road->setOwner(index);
                                    deleteResources(resources);
                                    std::cout << "now road have index of player owner" << road->getOwner()+1 << std::endl;
                                    return;
                                }
                                else
                                {
                                    std::cout << " you dont have Enough resources to place Road" << std::endl;
                                    return;
                                }
                            }
                            else
                            {
                                road->setOwner(index);
                                std::cout << "Placed Road in "<<land->getNum() <<" with Resource "<< resourceToString(land->getResource()) <<std::endl;

                                return;
                            }
                        }
                        else
                        {
                            std::cout << "no avilable road in this land. " << std::endl;
                            continue;
                        }
                    }
                }
            }
        }
        std::cout << "didnt found a road at all lands " << std::endl;
    }

    Road *Player::checkAvilableRoads(Land *land)
    {
        if (land == nullptr){
            return nullptr;
        }
        Road *avilableRoad = nullptr;
        std::vector<Road *> &roads = land->getRoads();
        //loop on current land roads
        for (size_t i = 0; i < roads.size(); i++)
        {
            Road *currRoad = roads[i];
            int ownerIndex = currRoad->getOwner();
            // check for road that the same player is own;
            if (index == ownerIndex)
            {
                // Looking for near road that have no owner;
                if (i > 0 && roads[i - 1]->getOwner() == -1)
                {
                    return roads[i - 1];
                }
                if (i + 1 < roads.size() && roads[i + 1]->getOwner() == -1)
                {
                    return roads[i + 1];
                }
                continue;
            }
            if (ownerIndex == -1)
            {
                //if the player owns one of the settelments of the road we want it;
                if(currRoad->getVertex1()->getOwner() == index || currRoad->getVertex2()->getOwner() == index){
                    return roads[i];
                }
                //else it no owner road - only for the first rounds its ok;
                avilableRoad = currRoad;
            }
        }

        return avilableRoad;
    }

    Vertex *Player::checkAvilableVertex(Land *land)
    {
        if (land == nullptr)
            return nullptr;
        vector<Vertex *> &vertices = land->getVertices();
        std::vector<Road*>& roads = land->getRoads();
        for (Vertex *v : vertices)
        {
            // check if there is empty vertex and it has also road that connect it.
            if (v->getOwner() == -1)
            {
                if (ownNeighborRoad(v) && !isNeighborVertex(v))
                {
                    return v;
                }
            }
        }
        return nullptr;
    }

    bool Player::ownNeighborRoad(Vertex *v)
    {
        vector<Road *> &neighborRoads = v->getNeighborRoads();
        for (Road *road : neighborRoads)
        {
            if (road->getOwner() == index)
            {
                return true;
            }
        }
        return false;
    }

    Vertex *Player::checkForSettelment(Land *land)
    {
        if (land == nullptr)
            return nullptr;
        vector<Vertex *> &vertices = land->getVertices();
        for (Vertex *v : vertices)
        {
            // check if this there is settelement this players owns;
            if (v->getOwner() == index)
            {
                return v;
            }
        }
        return nullptr;
    }

    bool Player::isNeighborVertex(Vertex *v)
    {
        vector<Vertex *> &neighborVer = v->getNeighhborsVertices();
        for (Vertex *v : neighborVer)
        {
            if (v->getOwner() != -1)
            {
                return true;
            }
        }
        return false;
    }

    void Player::addPoint()
    {
        this->points++;
    }

    void Player::claimResource(Vertex *v, vector<vector<Land *>> &lands)
    {
        bool isCity = v->getisCity();
        for (auto &row : lands)
        {
            for (Land *land : row)
            {
                if (land != nullptr)
                {
                    if (land->isContainVertex(v))
                    {
                        Resource res = land->getResource();
                        if (resourceToString(res) != "DESERT")
                        {
                            resourceCards.push_back(ResourceCard(resourceToString(res)));
                            std::cout << "player " << this->getIndex()+1 <<" got " << resourceToString(res) <<std::endl;
                            if(isCity){
                            //he need to get another one
                             resourceCards.push_back(ResourceCard(resourceToString(res)));
                            }
                        }
                    }
                }
            }
        }
    }

    void Player::addResourceCard(Resource res)
    {
        string resourceType = resourceToString(res);
        this->resourceCards.push_back(ResourceCard(resourceType));
    }

    bool Player::haveEnoughResource(std::vector<Resource> resources)

    { //count the resources the player need to have;
        std::map<Resource, int> requiredResourceCount;
        for ( auto &resource : resources)
        {
            requiredResourceCount[resource]++;
        }

        std::map<Resource, int> availableResourceCount;
        for ( auto &resourceCard : this->resourceCards)
        {
            for ( auto &pair : requiredResourceCount)
            {
                if (resourceCard.name == resourceToString(pair.first))
                {
                    availableResourceCount[pair.first]++;
                }
            }
        }

        // Step 3: Check if we have enough of each resource
        for (auto &pair : requiredResourceCount)
        {
            if (availableResourceCount[pair.first] < pair.second)
            {
                return false;
            }
        }
        return true;
    }

    bool Player::isResourceInResourceCard(Resource resource)
    {
        for (auto &resourceCard : this->resourceCards)
        {
            if (resourceCard.name == resourceToString(resource))
            {
                return true;
            }
        }
        return false;
    }


    void Player::addDevolpmentCard(DevelopmentCard devCard){
        this->developmentCards.push_back(devCard);
        if(devCard.name == "knights"){
            this->knightsCount++;
        }
    }

    void Player::useMonopoleCard(vector<Player*>& players,Resource resource){
        if(isGameOver){
           throw runtime_error("Game is over");
           return;
        }
        if(!checkTurn()){
            throw::runtime_error("not your turn");
        }
            //checking that the player have the card;
           int index = getDevolopmentCardIndex("monopole");
                if (index == -1)
                {
                 throw::runtime_error("you dont have monople card!");
                }else{
                    deleteDevelopmentCardByIndex(index);
                    for (size_t i = 0; i < players.size(); i++)
                    {
                        //taking from other players if they have the resource;
                        if(i != this->getIndex()){
                            int deleted = players[i]->deleteResource(resource);
                            if(deleted !=-1){
                                this->addResourceCard(resource);
                                std::cout << "added resource card from player "<< i <<" " << resourceToString(resource) <<std::endl;
                            }
                        }
                    }
                    endTurn(players);


           }



    }

    int Player::getDevolopmentCardIndex(string cardType){
        for (size_t i = 0; i < developmentCards.size(); i++)
        {
            if(developmentCards[i].name == cardType){
                return static_cast<int>(i);
            }
        }
        return -1;

    }

    void Player::usePlentyYearCard(vector<Resource> resourceToGetfromBank,vector<Player*>& players){
         if(isGameOver){
           throw runtime_error("Game is over");
           return;
        }
        if(!this->checkTurn()){
            throw runtime_error("it not your turn");
        }
        int PlentyIndex = getDevolopmentCardIndex("plentYear");
        if(PlentyIndex == -1){
             throw runtime_error("you dont have plenty year card");
        }
        if(resourceToGetfromBank.size() != 2){
            throw runtime_error("you can only get 2 resources");
        }else{
            deleteDevelopmentCardByIndex(PlentyIndex);
            endTurn(players);
            for(Resource resource : resourceToGetfromBank){
                this->addResourceCard(resource);
             }
        }
     }

    void Player::useBuildingRoadsCard(vector<vector<Land*>>& lands,vector<Player*>& players){
        if(!this->checkTurn()){
            throw runtime_error("it not your turn");
        }
        int BuildRoadIndex = getDevolopmentCardIndex("roadBuild");
        //making sure he has the card!
        if(BuildRoadIndex == -1){
             throw runtime_error("you dont have roadbuild card");
        }
        deleteDevelopmentCardByIndex(BuildRoadIndex);
        endTurn(players);
        int countRoadSetted = 0;
         for (auto &row : lands)
        {
            for (Land *land : row)
            {
                if (land != nullptr)
                {
                    Road* road = checkAvilableRoads(land);
                    if(road != nullptr){
                        road->setOwner(this->index);
                        countRoadSetted++;
                        if(countRoadSetted == 2) return;
                    }
                }
            }
        }
        std::cout << "i didnt found 2 roads avilable - only " << countRoadSetted << std::endl;

    }


    void Player::deleteDevelopmentCardByIndex(int index){
        if(index >=0 && index < this->developmentCards.size()){
            developmentCards[index].name == "knight";
            knightsCount--;
            this->developmentCards.erase(this->developmentCards.begin()+index);
        }
    }

    int Player::getKnightsCount(){
        return knightsCount;
    }

    void Player::deleteResources(std::vector<Resource> resources)
    {
        for (auto &resource : resources)
        {
            for (auto it = this->resourceCards.begin(); it != this->resourceCards.end(); ++it)
            {
                if (it->name == resourceToString(resource))
                {
                    this->resourceCards.erase(it);
                    break;
                }
            }
        }
    }

    int Player::deleteResource(Resource resource){
        int resIndex = getResourceIndex(this->getResourceCards() , resource);
        if(resIndex != -1){
            this->resourceCards.erase(this->resourceCards.begin()+resIndex);
        }
        return resIndex;

    }

    bool Player::tradeResource(Player &player, Resource resource1, Resource resource2)
    {
         if(isGameOver){
           throw runtime_error("Game is over");
           return false;
        }
        if (!checkTurn())
        {
            std::cout << "this isn't your turn!" << std::endl;
            return false;
        }
        int index1 = getResourceIndex(this->getResourceCards(), resource1);
        int index2 = getResourceIndex(player.getResourceCards(), resource2);
        if (index1 != -1 && index2 != -1)
        {
            ResourceCard res1 = ResourceCard(resourceToString(resource1));
            ResourceCard res2 = ResourceCard(resourceToString(resource2));

            this->getResourceCards().push_back(res2);
            this->getResourceCards().erase(this->getResourceCards().begin() + index1);

            player.getResourceCards().push_back(res1);
            player.getResourceCards().erase(player.getResourceCards().begin() + index2);
            return true;
        }
        std::cout << " one of you dont have the resource, trade didnt hapen" << std::endl;

        return false;
    }

    bool Player::tradeDevolpmentCards(Player& player, DevelopmentCard devCard1 , DevelopmentCard devCard2,bool armyCardLeft){
        if(isGameOver){
           throw runtime_error("Game is over");
           return false;
        }
        if (!checkTurn())
        {
            throw runtime_error("It isnt your turn");
            return false;
        }
        int index1 = getDevolopmentCardIndex(devCard1.name);
        int index2 = player.getDevolopmentCardIndex(devCard2.name);
        if (index1 != -1 && index2 != -1)
        {
            if(devCard1.name == "knight" && this->getKnightsCount()==3){
                this->decreasePoint();
                this->decreasePoint();
                if(player.getKnightsCount()==2 && armyCardLeft){
                    player.addPoint();
                    player.addPoint();
                }

            }
            if(devCard2.name == "knight" && player.getKnightsCount()==3){
                player.decreasePoint();
                player.decreasePoint();

            if(this->getKnightsCount()==2 && armyCardLeft){
                    this->addPoint();
                    this->addPoint();
                }
            }
                this->deleteDevelopmentCardByIndex(index1);
                player.deleteDevelopmentCardByIndex(index2);
                player.addDevolpmentCard(devCard1);
                this->addDevolpmentCard(devCard2);
            return true;
        }
        throw runtime_error("NOT posibole trade");

        return false;
    }


    void Player::changeTurn(bool boolean)
    {
        this->isHisTurn = boolean;
    }

    void Player::endTurn(vector<Player*>& players)
    {
        this->isHisTurn = false;
        int nextTurn = (index + 1)%3;
        players[nextTurn]->changeTurn(true);
        if (players[nextTurn]->isPlayerWon())
        {
            for(Player* player : players){
                player->setIsGameOver();
            }
            std::cout << "We have a winner! player " << nextTurn + 1  << " has Reached to " << players[nextTurn]->getPoints() << std::endl;
        }
    }

    int Player::rollDice(vector<vector<Land*>>& lands , vector<Player*>& players)
    {
    if(isGameOver){
           throw runtime_error("Game is over");
           return -1;
        }
    if (!checkTurn())
        {
            throw runtime_error("It isnt your turn");
            return false;
        }
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int outCome =dice1+dice2;
        std::cout << "roll Dice is - " << outCome <<std::endl;
        if(outCome == 7){
            cutResourceCards(players);
        }else{
            handleDice(outCome , lands , players);
        }
        return dice1 + dice2;
    }

    void Player::cutResourceCards(vector<Player*>& players){
        for(Player* player : players){
            if(player->getResourceCards().size() > 7) {
                std::cout << "cutting plaayer card number " << player->getIndex()+1 << " has " <<player->getResourceCards().size() <<std::endl;
                size_t halfSize = player->getResourceCards().size()/2;
                player->getResourceCards().erase(player->getResourceCards().begin(), player->getResourceCards().begin() + halfSize);
                std::cout << "now player number " << player->getIndex()+1 << " has " <<player->getResourceCards().size() <<std::endl;
            }
        }

    }

    void Player::handleDice(int diceOutcome , vector<vector<Land*>>& lands,vector<Player*>& players){
        for (auto &row : lands)
        {
            for (Land *land : row)
            {
                if (land != nullptr)
                {
                    int landNum = land->getNum();
                    if(landNum == diceOutcome){
                        Resource res = land->getResource();
                        vector<Vertex*> vertices = land->getVertices();
                        for(Vertex* v : vertices){
                            if(v->getOwner() != -1){
                                players[v->getOwner()]->addResourceCard(res);
                                std::cout << "player " <<v->getOwner()+1 << " got " << resourceToString(res) <<std::endl;
                                if(v->getisCity()){
                                    players[v->getOwner()]->addResourceCard(res);
                                    std::cout << "player " <<v->getOwner()+1 << " got another " << resourceToString(res) <<std::endl;

                                }

                            }
                        }
                    }
                }
            }
        }
    }

    // getters
    int Player::getPoints()
    {
        int pointsAmount =0;
        for(DevelopmentCard devCard : this->developmentCards){
            if(devCard.name =="victoryPoint"){
                pointsAmount++;
            }
        }
        pointsAmount+=this->points;
        return pointsAmount;
    }
    string Player::printPlayer() const
    {
        return name;
    }
    int Player::getIndex()
    {
        return index;
    }
    void Player::decreasePoint(){
        this->points--;
    }


    int Player::getResourceIndex(std::vector<ResourceCard> &resourceCard, Resource res)
    {
        for (size_t i = 0; i < resourceCard.size(); i++)
        {

            if (resourceCard[i].name == resourceToString(res))
            {
                return i;
            }
        }
        return -1;
    }

    std::vector<ResourceCard>& Player::getResourceCards()
    {
        return this->resourceCards;
    }
    std::vector<DevelopmentCard>& Player::getDevolopmentCards(){
        return this->developmentCards;
    }
    bool Player::isPlayerWon()
    {
        return (this->getPoints()>=10);
    }
    bool Player::checkTurn()
    {
        return this->isHisTurn;
    }

    void Player::printPoints()
    {
        std::cout << " player " << index << " have " << points << " points" << std::endl;
    }
    void Player::setIsGameOver(){
        this->isGameOver = true;
    }

}
