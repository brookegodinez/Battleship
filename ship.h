#ifndef __SHIP_H__
#define __SHIP_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Ship {
    protected:
        int health;
 	int length;
	string name;
	vector<vector<int>> coords; //ex: {{0, 1}, {0, 2}} 

    public:
	string get_name() { return name; }
	int get_length() { return length; }
 	int get_health() { return health; }
	void set_coords(vector<vector<int>> coords) { this->coords = coords; }
	vector<vector<int>> get_coords() {
	    /**for (unsigned i = 0; i < coords.size(); i++ ) {
	        cout << coords[i][0] << " " << coords[i][1] << endl;
	    }**/

	    return coords;
	}
	bool is_hit(vector<int> pair) {
	    for (unsigned i = 0; i < coords.size(); i++) {
	        if (pair.at(0) == coords[i][0] && pair.at(1) == coords[i][1]) {
 		    decr_health();
		    return true;
		}
	    }

	    return false;
 	}
	void decr_health() {
	    health--;
	}
	bool is_sunk() {
	    if (health == 0) {
		cout << get_name() << " has sunk!" << endl;
		return true;
	    }

	    return false;
	}

	//bool is_miss(); necessary? is_hit = false / miss
	//string get_coords();  just one square or entire vector?
};

class Carrier : public Ship {
    public:
	Carrier() {
	    health = 5;
	    length = 5;
	    name = "Carrier";
	}
};

class Battleship: public Ship {
    public:
	Battleship() {
	    health = 4;
	    length = 4;
	    name = "Battleship";
	}
};

class Destroyer : public Ship {
    public:
	Destroyer() {
	    health = 3;
	    length = 3;
	    name = "Destroyer";
	}
};

class Submarine : public Ship {
    public:
	Submarine() {
	    health = 3;
	    length = 3;
	    name = "Submarine";
	}
};

class PatrolBoat : public Ship {
    public:
	PatrolBoat() {
	    health = 2;
	    length = 2;
	    name = "Patrol Boat";
	}
};

#endif // __SHIP_H__