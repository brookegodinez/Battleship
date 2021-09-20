#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "ship.h"

using namespace std;

class Factory {
    public:
        virtual Ship* createCarrier() = 0;		
        virtual Ship* createBattleship() = 0;
	virtual Ship* createDestroyer() = 0;
	virtual Ship* createSubmarine() = 0;
	virtual Ship* createPatrolBoat() = 0;
	virtual string getFactoryType() = 0;
};

class PlayerShipFactory : public Factory {
    public:
        Ship* createCarrier() { return new Carrier; }
     	Ship* createBattleship() { return new Battleship; }
	Ship* createDestroyer() { return new Destroyer; }
	Ship* createSubmarine() { return new Submarine; }
	Ship* createPatrolBoat() { return new PatrolBoat; }
 	string getFactoryType() { return "player"; }
	 
};

class CompShipFactory : public Factory {
    public:
	Ship* createCarrier() { return new Carrier; }
        Ship* createBattleship() { return new Battleship; }
        Ship* createDestroyer() { return new Destroyer; }
        Ship* createSubmarine() { return new Submarine; }
        Ship* createPatrolBoat() { return new PatrolBoat; }
	string getFactoryType() { return "comp"; };
};

#endif // __FACTORY_H__
