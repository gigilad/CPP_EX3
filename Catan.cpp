//gilada8892@gmail.com

#include "Catan.hpp"
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <stdexcept>

using namespace std;

namespace ariel
{
    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);
        for (size_t i = 0; i < 14; i++)
        {
            this->developmentCards.push_back(DevelopmentCard("knight"));
            if (i < 3)
            {
                this->developmentCards.push_back(DevelopmentCard("victoryPoint"));
            }
            if (i < 2)
            {
                this->developmentCards.push_back(DevelopmentCard("monopole"));
                this->developmentCards.push_back(DevelopmentCard("roadBuild"));
                this->developmentCards.push_back(DevelopmentCard("plentYear"));
            }
        }
    }

    void Catan::setBoard(const Board &gameBoard)
    {
        board = gameBoard;
        this->getPlayers()[0]->changeTurn(true);
    }

    void Catan::buyDevelopmentCard(Player *player)
    {
        if(isGameOver){
           throw runtime_error("Game is over");
           return;
        }
        if (!player->checkTurn())
        {
            throw runtime_error("Its not your turn");
            return;
        }
        vector<Resource> resourceForDevelopmentCard = {Resource::IRON, Resource::WOOL, Resource::OATS};
        // If there are still devolopment cards left
        //  Get random card
        if (!developmentCards.empty())
        {
            if (player->haveEnoughResource(resourceForDevelopmentCard))
            {
                DevelopmentCard devCard = getDevelopmentCard();
                player->deleteResources(resourceForDevelopmentCard);
                player->addDevolpmentCard(devCard);
                if(devCard.name =="knight" && player->getKnightsCount() == 3){
                    if(this->biggerArmyCard > 0){
                        biggerArmyCard--;
                        player->addPoint();
                        player->addPoint();
                    }
                }
                std::cout << "Player " << player->getIndex()+1 << " got " << devCard.name << " card " << std::endl;
            }
            else
            {
                throw std::runtime_error("you dont have enough resources to buy development card");
            }
        }
    }

    DevelopmentCard Catan::getDevelopmentCard()
    {
        if (developmentCards.empty())
        {
            throw std::out_of_range("No cards available in the vector.");
        }

        // seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Generate random index
        int randomIndex = std::rand() % developmentCards.size();
        DevelopmentCard selectedCard = developmentCards[randomIndex];
        developmentCards.erase(developmentCards.begin() + randomIndex);
        return selectedCard;
    }

    void Catan::printPlayers() const
    {
        for (const Player *player : players)
        {
            cout << player->printPlayer() << endl;
        }
    }


    void Catan::printWinner(){
        for(Player* player : players){
            //if it his turn and he got to 10 points
            if(player->checkTurn() && player->isPlayerWon()){
                std::cout << " player " << player->getIndex()+1 <<" won " <<std::endl;
                this->isGameOver = true;
            }
        }
    }
    void Catan::giveResource(int rollDice)
    {
        vector<Vertex *> &vecs = board.getVertices();
        for (Vertex *v : vecs)
        {
            if (v->getOwner() != -1)
            {
                for (Resource r : v->getResources())
                {
                    players[v->getOwner()]->addResourceCard(r);
                    std::cout << "Player " << v->getOwner()+1 << " got resource card of " << resourceToString(r) << std::endl;
                    if (v->getisCity())
                    {
                        players[v->getOwner()]->addResourceCard(r);
                        std::cout << "Player " << v->getOwner()+1 << " got ANOTHER resource card of " << resourceToString(r) << std::endl;
                    }
                }
            }
        }
    }

    // getters
    vector<vector<Land *>> &Catan::getBoard()
    {
        return board.getBoard();
    }

    vector<Player *> &Catan::getPlayers()
    {
        return players;
    }
    bool Catan::getArmyCard(){
        return (biggerArmyCard>0);
    }

}
