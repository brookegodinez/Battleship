#ifndef __SHIP_TEST_HPP__
#define __SHIP_TEST_HPP__

#include "factory.h"
#include "ship.h"

#include <vector>

TEST(ShipTest, Carrier) {
    Factory* playerFactory = new PlayerShipFactory();
    Factory* compFactory = new CompShipFactory();
    Ship* ship;
 
    ship = playerFactory->createCarrier();
    EXPECT_EQ("Carrier", ship->get_name());
    EXPECT_EQ(5, ship->get_length());
    EXPECT_EQ(5, ship->get_health());
    ship = compFactory->createCarrier();
    EXPECT_EQ("Carrier", ship->get_name());
    EXPECT_EQ(5, ship->get_length());
    EXPECT_EQ(5, ship->get_health());
}

TEST(ShipTest, Battleship) {
    Factory* playerFactory = new PlayerShipFactory();
    Factory* compFactory = new CompShipFactory();
    Ship* ship;

    ship = playerFactory->createBattleship();
    EXPECT_EQ("Battleship", ship->get_name());
    EXPECT_EQ(4, ship->get_length());
    EXPECT_EQ(4, ship->get_health());
    ship = compFactory->createBattleship();
    EXPECT_EQ("Battleship", ship->get_name());
    EXPECT_EQ(4, ship->get_length());
    EXPECT_EQ(4, ship->get_health());
}

TEST(ShipTest, Destroyer) {
    Factory* playerFactory = new PlayerShipFactory();
    Factory* compFactory = new CompShipFactory();
    Ship* ship;

    ship = playerFactory->createDestroyer();
    EXPECT_EQ("Destroyer", ship->get_name());
    EXPECT_EQ(3, ship->get_length());
    EXPECT_EQ(3, ship->get_health());
    ship = compFactory->createDestroyer();
    EXPECT_EQ("Destroyer", ship->get_name());
    EXPECT_EQ(3, ship->get_length());
    EXPECT_EQ(3, ship->get_health());
}

TEST(ShipTest, Submarine) {
    Factory* playerFactory = new PlayerShipFactory();
    Factory* compFactory = new CompShipFactory();
    Ship* ship;

    ship = playerFactory->createSubmarine();
    EXPECT_EQ("Submarine", ship->get_name());
    EXPECT_EQ(3, ship->get_length());
    EXPECT_EQ(3, ship->get_health());
    ship = compFactory->createSubmarine();
    EXPECT_EQ("Submarine", ship->get_name());
    EXPECT_EQ(3, ship->get_length());
    EXPECT_EQ(3, ship->get_health());
}

TEST(ShipTest, PatrolBoat) {
    Factory* playerFactory = new PlayerShipFactory();
    Factory* compFactory = new CompShipFactory();
    Ship* ship;

    ship = playerFactory->createPatrolBoat();
    EXPECT_EQ("Patrol Boat", ship->get_name());
    EXPECT_EQ(2, ship->get_length());
    EXPECT_EQ(2, ship->get_health());
    ship = compFactory->createPatrolBoat();
    EXPECT_EQ("Patrol Boat", ship->get_name());
    EXPECT_EQ(2, ship->get_length());
    EXPECT_EQ(2, ship->get_health());
}

TEST(CoordsTest, Coords) {
    Factory* playerFactory = new PlayerShipFactory();
    Ship* ship;
    vector<int> pair;
    vector<int> checkPair;
    vector<vector<int>> coords;
    vector<vector<int>> checkCoords;

    ship = playerFactory->createCarrier();
    for (unsigned i = 0; i < ship->get_length(); i++) {
 	pair.push_back(0);
  	pair.push_back(i);
	coords.push_back(pair);
 	pair.clear();
    }
    
    ship->set_coords(coords);
    checkCoords = ship->get_coords();
    for (unsigned i = 0; i < ship->get_length(); i++) {
	pair = coords.at(i);
	checkPair = checkCoords.at(i);

 	EXPECT_EQ(pair[0], checkPair[0]);
	EXPECT_EQ(pair[1], checkPair[1]);
    }
}

TEST(HitTest, Hit) {
    Factory* playerFactory = new PlayerShipFactory();
    Ship* ship;
    ship = playerFactory->createPatrolBoat();
    vector<vector<int>> coords {{0,0}, {0,1}};
    bool hit;

    ship->set_coords(coords);
    hit = ship->is_hit({0, 0});
    EXPECT_TRUE(hit);
    hit = ship->is_hit({0, 2});
    EXPECT_FALSE(hit);
}

TEST(HealthTest, DecrHealth) {
    Factory* playerFactory = new PlayerShipFactory();
    Ship* ship;
    ship = playerFactory->createPatrolBoat();
    vector<vector<int>> coords {{0,0}, {0,1}};
    bool hit;

    ship->set_coords(coords);
    EXPECT_EQ(2, ship->get_health());
    hit = ship->is_hit({0,0});
    EXPECT_EQ(1, ship->get_health());
    hit = ship->is_hit({0,2});
    EXPECT_EQ(1, ship->get_health());
    hit = ship->is_hit({0,1});
    EXPECT_EQ(0, ship->get_health());
} 

TEST(SunkTest, Sunk) {
    Factory* playerFactory = new PlayerShipFactory();
    Ship* ship;
    ship = playerFactory->createPatrolBoat();
    vector<vector<int>> coords {{0,0}, {0,1}};
    bool hit, sunk;

    ship->set_coords(coords);
    sunk = ship->is_sunk();
    EXPECT_FALSE(sunk);
    hit = ship->is_hit({0,0});
    sunk = ship->is_sunk();
    EXPECT_FALSE(sunk);
    hit = ship->is_hit({0,2});
    sunk = ship->is_sunk();
    EXPECT_FALSE(sunk);
    hit = ship->is_hit({0,1});
    sunk = ship->is_sunk();
    EXPECT_TRUE(sunk);
}

#endif //__SHIP_TEST_HPP__
