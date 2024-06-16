
//gilada8892@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "doctest.h"
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <cstdlib>
#include <ctime>

using namespace ariel;
using namespace std;

TEST_CASE("checking initialize hex board"){
    srand(static_cast<unsigned int>(time(0)));
    // Create Catan object with three players
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);

    Catan Catan(player1, player2, player3);
    Catan.printPlayers();
    Board Board;
    Catan.setBoard(Board);
     vector<vector<Land*>>& lands = Catan.getBoard();
    map<Resource,int> countResource={
            {Resource::WOOD, 0},
            {Resource::BRICK, 0},
            {Resource::WOOL, 0},
            {Resource::OATS, 0},
            {Resource::IRON, 0},
            {Resource::DESERT, 0},
             {Resource::NONE, 0}
        };
    map<int,int> numberOnLands = {
            {2 , 0},
            {3 , 0},
            {4 , 0},
            {5 , 0},
            {6 , 0},
            {8 , 0},
            {9 , 0},
            {10 , 0},
            {11 , 0},
            {12 , 0}
        };

    CHECK(lands[0][0] == nullptr);
    CHECK(lands[0][1] == nullptr);
    CHECK(lands[1][0] == nullptr);
    CHECK(lands[4][3] == nullptr);
    CHECK(lands[3][4] == nullptr);
    CHECK(lands[4][4] == nullptr);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++){
            if (lands[i][j] != nullptr){
            Resource res =lands[i][j]->getResource();
            countResource[res]++;
            int num = lands[i][j]->getNum();
            numberOnLands[num]++;
            }
        }
    }
    CHECK(countResource[Resource::DESERT] == 1);
    CHECK(countResource[Resource::WOOD] == 4);
    CHECK(countResource[Resource::WOOL] == 4);
    CHECK(countResource[Resource::IRON] == 3);
    CHECK(countResource[Resource::BRICK] == 3);
    CHECK(countResource[Resource::OATS] == 4);
    // CHECK(countResource[Resource::NONE] == 6);
    for (const auto& num : numberOnLands){
        cout << "key " << num.first << " val "<< num.second << endl;

    }


    CHECK(numberOnLands[2]==1);
    CHECK(numberOnLands[3]==2);
    CHECK(numberOnLands[4]==2);
    CHECK(numberOnLands[5]==2);
    CHECK(numberOnLands[6]==2);
    CHECK(numberOnLands[8]==2);
    CHECK(numberOnLands[7]==0);
    CHECK(numberOnLands[10]==2);
    CHECK(numberOnLands[11]==2);
    CHECK(numberOnLands[12]==1);




}


TEST_CASE("CHECKING OPERATOR == Beetwen vertices and roads"){
    Vertex v1 = Vertex(2,3);
    Vertex v2 = Vertex(3,5);
    Vertex v3 = Vertex(2,3);

    CHECK((v1==v2) == 0);
    CHECK((v2==v3) == 0);
    Vertex v4(1, 2);
    Vertex v5(3, 4);
    Vertex v6(1, 2); // Same as v1 for testing

    // Create roads
    Road r1(&v4, &v5);
    Road r2(&v5, &v6);

    CHECK(r1 == r2);

}

TEST_CASE("CHECKING neighbrhood vertices"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);

    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    vector<Vertex*>& vertices = Board.getVertices();
    CHECK(vertices.size() == 54);

    Vertex v1(1, 2);
    Vertex v2(3, 4);
    Vertex v3(5, 6);
    Vertex v4(3, 4); // Same coordinates as v2

    // Add neighbors
    v1.addNeighborVertex(&v2);
    v1.addNeighborVertex(&v3);
    v1.addNeighborVertex(&v4);

    CHECK(v1.getNeighhborsVertices().size() == 2);

}

TEST_CASE("Checking trade function"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    vector<Player*>& players = Catan.getPlayers();
    vector<vector<Land*>>& lands = Catan.getBoard();
    Board.printBoard();
    player1.addResourceCard(Resource::BRICK);
    player2.addResourceCard(Resource::OATS);
    player2.addResourceCard(Resource::WOOL);
    bool trade = player1.tradeResource(player2 , Resource::BRICK,Resource::WOOL);
    CHECK(trade == 1);

    bool trade2=player2.isResourceInResourceCard(Resource::BRICK);
    bool trade3=player2.isResourceInResourceCard(Resource::WOOL);
    CHECK(trade2 == 1); // player 2 got brick from the trade;
    CHECK(trade3 == 0); // player 2 gave his wool;
    bool trade4=player1.isResourceInResourceCard(Resource::BRICK);
    bool trade5=player1.isResourceInResourceCard(Resource::WOOL);
    CHECK(trade5 == 1); // player 1 got brick from the trade;
    CHECK(trade4 == 0); // player 1 gave his wool;

    player1.endTurn(players);
    //not his turn
    bool trade6 = player1.tradeResource(player2 , Resource::BRICK,Resource::WOOL); //not player 1 turn anymore;
    CHECK(trade6 ==false);

}

TEST_CASE("Checking trade function"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    player1.addResourceCard(Resource::BRICK);
    player1.addResourceCard(Resource::BRICK);
    player1.addResourceCard(Resource::WOOD);
    player1.addResourceCard(Resource::WOOL);
    player1.addResourceCard(Resource::WOOL);
    player1.addResourceCard(Resource::BRICK);
    player1.addResourceCard(Resource::WOOL);
    player1.addResourceCard(Resource::DESERT);

    std::vector<Resource> resources = {Resource::BRICK, Resource::WOOD, Resource::WOOL, Resource::WOOL, Resource::WOOL ,Resource::BRICK , Resource::BRICK};
    bool result = player1.haveEnoughResource(resources);
    CHECK(result == true);

    player2.addResourceCard(Resource::BRICK);
    player2.addResourceCard(Resource::BRICK);
    player2.addResourceCard(Resource::WOOD);
    std::vector<Resource> resources1 = {Resource::BRICK, Resource::WOOD, Resource::WOOL, Resource::WOOL, Resource::WOOL ,Resource::BRICK , Resource::BRICK};
    bool result1 = player2.haveEnoughResource(resources1);
    CHECK(result1 == false);

    }
TEST_CASE("check devolpmentCards"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    vector<Player*>& players = Catan.getPlayers();
    int size =player1.getDevolopmentCards().size();
    CHECK(size == 0);

    player1.addResourceCard(Resource::IRON);
    player1.addResourceCard(Resource::WOOL);
    player1.addResourceCard(Resource::OATS);

    Catan.buyDevelopmentCard(&player1);
    int size1 =player1.getDevolopmentCards().size();
    CHECK(size1==1);
    try{
    Catan.buyDevelopmentCard(&player1);
    }catch(std::runtime_error& e){
        std::cerr << "Execption - "<< e.what() << std::endl;
    }
    //player1 have 2 resources
    player1.addResourceCard(Resource::BRICK);
    player1.addResourceCard(Resource::BRICK);
    player1.endTurn(players);
    //player2 need to have one development card and it monople
    player2.addDevolpmentCard(DevelopmentCard("monopole"));
    CHECK(player2.getDevolopmentCards().size() == 1);
    CHECK(player2.getDevolopmentCards()[0].name == "monopole");
    player2.useMonopoleCard(Catan.getPlayers() , Resource::BRICK);
    CHECK(player2.getResourceCards().size() == 1);
    CHECK(player2.getResourceCards()[0].name == "BRICK");
    CHECK(player1.getResourceCards().size() == 1);
    CHECK(player2.getDevolopmentCards().size() == 0);

}

TEST_CASE("testing handling dices roll"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    Board.printBoard();
    vector<Player*>& players = Catan.getPlayers();
    vector<vector<Land*>>& lands = Catan.getBoard();

    vector<int> placesNum ={4,5,6,9};
    vector<string> places = {"BRICK" , "OATS","WOOL"};
    player1.placeRoad(places , placesNum , lands);
    player1.placeSettelment(places , placesNum , lands);
    vector<int> placesNum1 ={4,10,3,9};
    vector<string> places1 = {"WOOD" , "OATS"};
    player1.placeRoad(places1 , placesNum1 , lands);
    player1.placeSettelment(places1 , placesNum1 , lands);

    player1.endTurn(players);

    player2.placeRoad(places , placesNum , lands);
    player2.placeSettelment(places , placesNum , lands);
    player2.placeRoad(places1 , placesNum1 , lands);
    player2.placeSettelment(places1 , placesNum1 , lands);

    player2.rollDice(lands,players);
    vector<ResourceCard>& resourceCards = player1.getResourceCards();
    for(ResourceCard res: resourceCards){
        std::cout << "player 0 have resoruce "<< res.name <<std::endl;
    }
    vector<ResourceCard>& resourceCards1 = player2.getResourceCards();
    for(ResourceCard res: resourceCards1){
        std::cout << "player 1 have resoruce "<< res.name <<std::endl;
    }
    std::cout << " not player 0 has " <<players[0]->getResourceCards().size()<<std::endl;
    std::cout << " not player 1 has " <<players[1]->getResourceCards().size()<<std::endl;


}
TEST_CASE("testing trade devolepment Cards "){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    Board.printBoard();
    vector<Player*>& players = Catan.getPlayers();
    vector<vector<Land*>>& lands = Catan.getBoard();
    CHECK(player1.getDevolopmentCards().size() == 0);
    player1.addDevolpmentCard(DevelopmentCard("buildRoad"));
    player2.addDevolpmentCard(DevelopmentCard("plentYear"));

    player1.tradeDevolpmentCards(player2 ,DevelopmentCard("buildRoad"),DevelopmentCard("plentYear"),Catan.getArmyCard());
    CHECK(player1.getDevolopmentCards().size() == 1);
    CHECK(player1.getDevolopmentCards()[0].name == "plentYear");
    CHECK(player2.getDevolopmentCards()[0].name == "buildRoad");

    try{
        //wont work now;
        player1.tradeDevolpmentCards(player2 ,DevelopmentCard("buildRoad"),DevelopmentCard("plentYear"),Catan.getArmyCard());

    }catch(std::runtime_error e){
        std::cout << e.what() <<std::endl;
    }


}

TEST_CASE("check if player win works"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    Board.printBoard();
    vector<Player*>& players = Catan.getPlayers();
    vector<vector<Land*>>& lands = Catan.getBoard();
    for (size_t i = 0; i < 11; i++)
    {
        player1.addPoint();
    }
    player1.endTurn(players);
    player2.endTurn(players);
    player3.endTurn(players);
}
TEST_CASE("check if dice == 7 works"){
    Player player1("Alice",0);
    Player player2("Bob",1);
    Player player3("Charlie",2);
    Catan Catan(player1, player2, player3);
    Board Board;
    Catan.setBoard(Board);
    Board.printBoard();
    vector<Player*>& players = Catan.getPlayers();
    CHECK(player1.getResourceCards().size()==0);
    for (size_t i = 0; i < 8; i++)
    {
        player1.addResourceCard(Resource::BRICK);
    }
    player1.cutResourceCards(players);
    CHECK(player1.getResourceCards().size()==4);
}