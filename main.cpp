/**
  *@authors: Brooke Godinez, Nathan Ng, Shankar Ramaswamy
 **/

#include "game.h"

#include <iostream>

using namespace std;

int main() {
    Game game;
    
    Factory* player = new PlayerShipFactory();
    Factory* computer = new CompShipFactory();
    string coord, temp;
    int smart;
    bool winner = false;
    bool valid;

    //cout << "\e[8;35;85t"; //resizes terminal
    //game.print_board();
    game.place_ships();
    cout << "Do you want a smart computer? Enter 1 for yes, 0 for no: ";
    cin >> smart;
  
    while(!winner){
        valid = false;
        while (!valid) {
	    game.print_guess(player);
            cout << "Attack your enemy! Enter coordinate: ";
            cin >> coord;

	    valid = game.valid_square(coord);
        }
        game.player_attack(player, coord, smart);

	winner = game.winner();

	if (winner)
	    break;

        cout << "Hit record: "; 
        game.get_hit_record();

	game.print_guess(computer);
        cout << "Computers move: ";
        game.player_attack(computer, coord, smart);
 	winner = game.winner();
    } 

    delete player;
    delete computer;

    return 0;
}
