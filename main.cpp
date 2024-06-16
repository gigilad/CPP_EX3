#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace ariel;

int main() {
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    Board.printBoard();
    vector<Player*>& players = Catan.getPlayers();
    vector<vector<Land*>>& lands = Catan.getBoard();

    //looking for land that have one of the number and one of the places;
    vector<int> placesNum ={4,5,6,9};
    vector<string> places = {"BRICK" , "OATS","WOOL"};
    player1.placeRoad(places , placesNum , lands);
    player1.placeSettelment(places , placesNum , lands);
    vector<int> placesNum1 ={10,3,9};
    vector<string> places1 = {"WOOD" , "OATS", "IRON"};
    player1.placeRoad(places1 , placesNum1 , lands);
    player1.placeSettelment(places1 , placesNum1 , lands);

    player1.endTurn(players);

    vector<int> placesNum2 ={2,8,11,12};
    vector<string> places2 = {"BRICK" ,"OATS","WOOL"};
    player2.placeRoad(places2 , placesNum2 , lands);
    player2.placeSettelment(places2 , placesNum2 , lands);
    vector<int> placesNum3 ={4,5,6,3};
    vector<string> places3 = {"WOOD" , "OATS", "IRON"};
    player2.placeRoad(places3 , placesNum3 , lands);
    player2.placeSettelment(places3 , placesNum3 , lands);

    player2.endTurn(players);
    vector<int> placesNum4 ={11,6,9};
    vector<string> places4 = {"BRICK" , "IRON","WOOL"};
    player3.placeRoad(places4 , placesNum4 , lands);
    player3.placeSettelment(places4 , placesNum4 , lands);
    vector<int> placesNum5 ={4,7,5,9};
    vector<string> places5 = {"WOOD" , "OATS", "BRICK"};
    player3.placeRoad(places5 , placesNum5 , lands);
    player3.placeSettelment(places5 , placesNum5 , lands);

    player3.endTurn(players);
    player1.rollDice(lands,players);
    try
    {
        // will work only if he has enough resources and if it his turn;
        Catan.buyDevelopmentCard(&player1);
        //will work only if he got randomly the plentYear card;
        player1.usePlentyYearCard({Resource::IRON , Resource::BRICK}, players);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    player1.endTurn(players);

    player2.rollDice(lands,players);

    vector<int> placesNum6 ={2,3,4,8,9};
    vector<string> places6 = {"WOOD" , "OATS", "IRON"};
    player2.placeRoad(places6 , placesNum6 , lands);
    player2.placeSettelment(places6 , placesNum6 , lands);

    player2.endTurn(players);
    try
    {
        // Not his turn
        player2.rollDice(lands,players);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    player3.rollDice(lands,players);
    try
    {
        //Will happend only if both have the resources and if it player 1 turn.
        player3.tradeResource(player1 ,Resource::BRICK , Resource::OATS);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    return 0;
}
