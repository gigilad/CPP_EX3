#ifndef CATAN_HPP
#define CATAN_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <iostream>

using namespace std;

namespace ariel {
    class Catan {
        private:
            vector<Player*> players;
            Board board;
            std::vector<DevelopmentCard> developmentCards;
            bool isGameOver = false;
            int biggerArmyCard = 3;

        public:
            Catan(Player& p1, Player& p2, Player& p3);
            void printPlayers() const;
            void setBoard(const Board& gameBoard);
            void giveResource(int diceRoll);
            vector<vector<Land*>>& getBoard();
            vector<Player*>& getPlayers();
            void buyDevelopmentCard(Player* player);
            DevelopmentCard getDevelopmentCard();
            bool getArmyCard();
            void printWinner();

    };
}

#endif // CATAN_HPP
