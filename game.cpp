#include "game.h"
#include "factory.h"
#include "ship.h"
#include "compstrat.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stdio.h> 
#include <stdlib.h>  //rand, color 
#include <time.h>    //time 
using namespace std;

Game::~Game() {
    for (unsigned i = 0; i < playerShips.size(); i++) {
        delete playerShips.at(i);
        delete compShips.at(i);
    }

    delete playerFactory;
    delete compFactory;
}

void Game::print_board(string board[][10]) {
    /**flush();

    print_char(' ', 4);

    for (char c = 'A'; c <= 'J'; c++) {
        cout << c << ' ';
    }

    cout << endl;

    for (unsigned i = 1; i <= 10; i++) {
        cout << i;
        print_char(' ', 1);
        if (i != 10)
            cout << ' ';

        for (unsigned j = 0; j < 10; j++) {
            cout << " " << ships[i-1][j];
        }

        cout << endl;
    }**/
  
    flush();

    //print column letters
    print_char(' ', 8);
    for (char c= 'A'; c<= 'J'; c++) {
	cout << c;
  	
	if (c!= 'J')
	    print_char(' ', 7);
    }

    cout << endl;

    //print dash lines below column letters
    print_char(' ', 5);
    print_char('-', 79);
    cout << endl;

    //prints the rows in tiers
    for (unsigned i = 1; i <= 10; i++) {
 	//tier 1
 	print_char(' ', 4);
	cout << "|";
    	for (unsigned j = 0; j < 10; j++) {
	    color("0", 3);
            color(board[i-1][j], 1);
	    color ("0", 3);
	    cout << "|";
	}
  	cout << endl;

 	//tier 2
 	cout << i;
	print_char(' ', 2);
	if (i != 10)
	    cout << ' ';
	cout << "|";
        for (unsigned j = 0; j < 10; j++) {
	    color("0", 2);
	    color(board[i-1][j], 3);
	    color("0", 2);
	    cout << "|";
	}
	cout << endl;

	//tier 3
	print_char(' ', 4);
	cout << "|";
 	for (unsigned j = 0; j < 10; j++) {
	    color("0", 3);
	    color(board[i-1][j], 1);
	    color("0", 3);
	    cout << "|";
	}
	cout << endl;

	//tier 4
	print_char(' ', 5);
        print_char('-', 79);
	cout << endl;
    }
}

void Game::print_char(char c, int num) {
    for (unsigned i = 0; i < num; i++) {
        cout << c;
    }
}

void Game::print_string(string str, int num) {
    for (unsigned i = 0; i < num; i++) {
        cout << str;
    }
}

void Game::flush() {
    cout << "\033[H\033[2J";	
}

void Game::color(string str, int num) {
    if (str == "0") {
        for (unsigned i = 0; i < num; i++) {
	    cout << "\033[1;104m \033[0m";
	}
    }

    else if (str == "1") {
        for (unsigned i = 0; i < num; i++) {
	    cout << "\033[1;100m \033[0m";
	}
    }
    
    else if (str == "X"){
        for (unsigned i = 0; i < num; i++) {
	    cout << "\033[1;101m \033[0m";
        }
    }

    else {
	for (unsigned i = 0; i < num; i++) {
	    cout << " ";
	}
    }
}

void Game::place_ships() {
    //Factory* playerFactory = new PlayerShipFactory;
    //Factory* compFactory = new CompShipFactory;

    Ship* ship;
    
    //player ships
    ship = playerFactory->createCarrier();
    set_ship(ship, ship->get_length(), playerFactory->getFactoryType(), playerBoard);
    playerShips.push_back(ship);   
    ship = playerFactory->createBattleship();
    set_ship(ship, ship->get_length(), playerFactory->getFactoryType(), playerBoard);
    playerShips.push_back(ship);
    ship = playerFactory->createDestroyer();
    set_ship(ship, ship->get_length(), playerFactory->getFactoryType(), playerBoard);
    playerShips.push_back(ship);
    ship = playerFactory->createSubmarine();
    set_ship(ship, ship->get_length(), playerFactory->getFactoryType(), playerBoard);
    playerShips.push_back(ship);
    ship = playerFactory->createPatrolBoat();
    set_ship(ship, ship->get_length(), playerFactory->getFactoryType(), playerBoard);
    playerShips.push_back(ship);

    print_board(playerBoard);
  
    flush();
    cout << "Readying enemy board..." << endl;

    //comp ships
    ship = compFactory->createCarrier();
    set_ship(ship, ship->get_length(), compFactory->getFactoryType(), compBoard);
    compShips.push_back(ship); 
    ship = compFactory->createBattleship();
    set_ship(ship, ship->get_length(), compFactory->getFactoryType(), compBoard);
    compShips.push_back(ship);
    ship = compFactory->createDestroyer();
    set_ship(ship, ship->get_length(), compFactory->getFactoryType(), compBoard);
    compShips.push_back(ship);
    ship = compFactory->createSubmarine();
    set_ship(ship, ship->get_length(), compFactory->getFactoryType(), compBoard);
    compShips.push_back(ship);
    ship = compFactory->createPatrolBoat();
    set_ship(ship, ship->get_length(), compFactory->getFactoryType(), compBoard);
    compShips.push_back(ship);
   
    /**for (unsigned i = 0; i < 5; i++) {
	ship = compShips.at(i);
	vector<vector<int>> coords = ship->get_coords();
	for (unsigned j = 0; j < ship->get_length(); j++) {
	    cout << coords[j][0] << coords[j][1] << " ";
	}
	cout << endl;
    }**/

    //delete playerFactory;
    //delete compFactory;	
  
    //COMMENT THIS OUT: use for testing only
    print_board(compBoard);
    
}

void Game::set_ship(Ship* ship, int length, string type, string board[][10]) {
    string start, end;
    int x1, x2, y1, y2;
    int orientation;
    vector<int> pair;
    vector<vector<int> > coords; 
    bool valid = false;
    
    while (!valid) {
	if (type == "player") {
	    x1 = -1; x2 = -1; y1 = -1; y2 = -1;

            print_board(playerBoard);
    	    cout << "Place your " << ship->get_name() << "(" << length << ")" << endl; 
	    cout << "Enter start coordinate: ";
    	    cin >> start;
	    cout << "Enter end coordinate: ";
            cin >> end;
 	    
	    if (start.length() <= 1 || end.length() <= 1) {
		x1 = -1;
		y1 = -1;
		x2 = -1;
		y2 = -1;
	    }
	
	    else {
	        x1 = convert_coord_row(start.substr(1));
                y1 = convert_coord_col(start.substr(0, 1));
   	        x2 = convert_coord_row(end.substr(1));
   	        y2 = convert_coord_col(end.substr(0, 1));
 	 	cout << x1 << y1 << x2 << y2 << endl;
	    }
	}

	else { //type == "comp"
 	    srand(time(NULL));
  	    orientation = rand() % 2; //0 = vertical, 1 = horizontal

	    if (orientation == 0) {
		x1 = rand() % 9;
		x2 = x1 + length - 1;
		y1 = rand() % 9;
		y2 = y1;
	    }

	    else {
	        x1 = rand() % 9;
	        x2 = x1;
	        y1 = rand() % 9;
	        y2 = y1 + length - 1;
	    }
	}
	
	valid = is_available(board, length, x1, x2, y1, y2);
    }  
    
    //swap if start and end aren't in order ex: (A5, A1)
    if ((x1 > x2 && y1 == y2) || (y1 > y2 && x1 == x2)) {
        swap(x1, x2);
        swap(y1, y2);
    }

    if (y1 == y2) {
        for (int i = x1; i <= x2; i++) {
            board[i][y1] = "1";
	    pair.push_back(i);
	    pair.push_back(y1);
	    coords.push_back(pair);
	    pair.clear();
        //cout << i;
        //cout << y1 << endl;
        }
        
    }

    else {
        for (int j = y1; j <= y2; j++) {
            board[x1][j] = "1";
	    pair.push_back(x1);
	    pair.push_back(j);
	    coords.push_back(pair);
	    pair.clear();
        }
    }
    
    ship->set_coords(coords);  
    
}

bool Game::is_available(string board[][10], int length, int x1, int x2, int y1, int y2) {
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)		//outside board
        return false;
    else if (x1 > 9 || x2 > 9 || y1 > 9 || y2 > 9)	//outside board
	return false;	
    else if (x1 == x2 && y1 == y2)			//entered same square
	return false;
    else if (x1 != x2 && y1 != y2)			//unrelated points; not linear
	return false;
    
    //swap if start and end aren't in order ex: (A5, A1)
    if ((x1 > x2 && y1 == y2) || (y1 > y2 && x1 == x2)) {
   	swap(x1, x2);
	swap(y1, y2);
    }

    if (y1 == y2) {
	if ((x2 - x1) != length - 1)
	    return false;

        for (int i = x1; i <= x2; i++) {
	    if (board[i][y1] == "1") {
		return false;
	    }
        }
    }

    else {
	if ((y2 -y1) != length -1)
	    return false;

        for (int i = y1; i <= y2; i++) {
   	    if (board[x1][i] == "1") {
	        return false;
	    }
	}
    }

    return true;
}

int Game::convert_coord_row(string str) {
    if (str.length() >= 3) {
        if (isdigit(str.at(0)) && isdigit(str.at(1))) {
	    if (str.at(0) == 1 && str.at(1) == 0)
	        return 9;
        }
    }

    else if (isdigit(str.at(0))) {
        return stoi(str) - 1;
    }

    return -1;
}

int Game::convert_coord_col(string str) {
    int col = 0;
    if (islower(str.at(0)))
	str.at(0) = toupper(str.at(0));

    for (char c = 'A'; c <= 'J'; c++) {
        if (c == str.at(0)) 
            return col;    

        else
	    col++;
    }


    return -1; //outside board
}
 
void Game::player_attack(Factory* ptr, std::string coord, int comp_strategy){
    int horz_coord = convert_coord_row(coord.substr(1));
    int vert = convert_coord_col(coord.substr(0, 1));
    bool right_guess = false;
    //int vert = 1;
    /**string str = coord.substr(1);
    while(vert <= 10){
        if(stoi(str) == vert){
            break;
                }
            vert++;
                }
    vert -= 1;**/

    //for checking if the player attacks on the compBoard
    if (ptr->getFactoryType() == "player"){
            //bool already_guessed = false;
            /**if (compBoard[horz_coord][vert] != ""){
                        already_guessed = false;
            }**/

	    /**for (unsigned i = 0; i < prev_guess.size(); i++) {
		if (coord == prev_guess.at(i)) {
		    already_guessed = true;
		    break;
		}   
	    }**/

        for (int k = 0; k < compShips.size(); k++){
            vector<vector<int> > ship_coords = compShips[k]->get_coords();
            for (int x = 0; x < ship_coords.size(); x++){
                if ((ship_coords[x][0] == horz_coord) && (ship_coords[x][1] == vert)){
                    right_guess = true;
                    hit_record.push_back(coord);
                    compShips[k]->decr_health();
                    cout << endl;
                    compBoard[horz_coord][vert] = "X"; 
		    guessBoard[horz_coord][vert] = "X";

		    print_board(guessBoard);
		    cout << "Hit! At: " << coord << endl;
		    if(compShips[k]->is_sunk()){
                        cout << "You've sunk the enemies battle ship" << endl;
                    }
            	    cout << "[Enter] to continue" << endl;
            	    cin.ignore();
                    cin.ignore();
                }
            }
        }
        if (!right_guess){
            compBoard[horz_coord][vert] = "";
	    guessBoard[horz_coord][vert] = "";
	    print_board(guessBoard);
	    cout << "You missed!" << endl;
            cout << "[Enter] to continue" << endl;
            cin.ignore();
            cin.ignore();
        }
        //if (already_guessed){ cout << "You have already made this move!" << endl;}      
    }        
    //if easy strategy using random guessing from the computer
    else if (ptr->getFactoryType() == "comp" && comp_strategy == 0){
        RandomGuess random;
        coord = random.computeStrategy(prev_guess_comp);
        int horz_coord = convert_coord_col(coord.substr(0,1));
        int vert = 1;
        prev_guess_comp.push_back(coord);
        string str = coord.substr(1);
        while(vert <= 10){
            if(stoi(str) == vert){
                break;
            }
            vert++;
        }
        vert -= 1;
        for (int k = 0; k < playerShips.size(); k++){
        vector<vector<int> > ship_coords1 = playerShips[k]->get_coords();
            for (int x = 0; x < ship_coords1.size(); x++){
                if ((ship_coords1[x][0] == vert) && (ship_coords1[x][1] == horz_coord)){
		    right_guess = true;
                    playerBoard[vert][horz_coord] = "X"; 
                    print_board(playerBoard);
                    cout << "You've been hit! At: " << coord << endl;
                    playerShips[k]->decr_health();
                    //playerBoard[horz_coord][vert] = "X"; 
                    if(playerShips[k]->is_sunk()){
                        cout << "You're " << playerShips[k]->get_name() << " is sunk!" << endl;
                    }
                }
            }
        }

	if (!right_guess) {
            playerBoard[vert][horz_coord] = "";
            print_board(playerBoard);
	    cout << "Computer missed!" << endl;
        }

	cout << "[Enter] to continue";
        cin.ignore();
    } 
    //for smart strategy, starts with a random selection
    else if (ptr->getFactoryType() == "comp" && comp_strategy == 1){
        //bool correct_guess = false;
        Context smart_guess(new HorizontalGuess);
        if (!correct_guess){
            RandomGuess random;
            coord = random.computeStrategy(prev_guess_comp);
            int horz_coord = convert_coord_col(coord.substr(0,1));
            int vert = 1;
            prev_guess_comp.push_back(coord);
            string str = coord.substr(1);
            while(vert <= 10){
                if(stoi(str) == vert){
                    break;
                }
                vert++;
            }
            vert -= 1;
            for (int k = 0; k < playerShips.size(); k++){
            vector<vector<int> > ship_coords1 = playerShips[k]->get_coords();
                for (int x = 0; x < ship_coords1.size(); x++){
                    if ((ship_coords1[x][0] == vert) && (ship_coords1[x][1] == horz_coord)){
                        playerBoard[vert][horz_coord] = "X"; 
                        print_board(playerBoard);
                        cout << "You've been hit! At: " << coord << endl;
                        playerShips[k]->decr_health(); 
                        correct_guess = true;
                        if(playerShips[k]->is_sunk()){
                            cout << "You're " << playerShips[k]->get_name() << " is sunk!" << endl;
                        }
                    }
                }
            }
        }
        
        else if (correct_guess){
            string coord = smart_guess.useStrategy(prev_guess_comp);
            cout << coord << endl;
            int horz = convert_coord_col(coord.substr(0,1));
            int vert = 1;
            prev_guess_comp.push_back(coord);
            string str = coord.substr(1);
            while(vert <= 10){
                if(stoi(str) == vert){
                    break;
                }
                vert++;
            }
            vert -= 1;
        
            for (int k = 0; k < playerShips.size(); k++){
                vector<vector<int> > ship_coords1 = playerShips[k]->get_coords();
                for (int x = 0; x < ship_coords1.size(); x++){
                    if ((ship_coords1[x][0] == vert) && (ship_coords1[x][1] == horz)){
                        playerBoard[vert][horz] = "X"; 
                        print_board(playerBoard);
                        cout << "You've been hit! At: " << coord << endl;
                        playerShips[k]->decr_health(); 
                        if(playerShips[k]->is_sunk()){
                            cout << "You're " << playerShips[k]->get_name() << " is sunk!" << endl;
                        }
                    }
                }
            } 
        } 
        cout << "[Enter] to continue";
        cin.ignore();
    }
}

bool Game::valid_square(string coord) {
    int x, y;
  
    if (coord.length() == 1) 
	return false;

    x = convert_coord_row(coord.substr(1));
    y = convert_coord_col(coord.substr(0, 1));
    
    for (unsigned i = 0; i < prev_guess.size(); i++) {
	if (coord == prev_guess.at(i)) {
	    return false;
	}
    }

    prev_guess.push_back(coord);

    return true;
}

bool Game::winner() {
    int playerCount = 0;
    int compCount = 0;

    for (unsigned i = 0; i < 5; i++) {
	if (playerShips.at(i)->get_health() == 0)
	    compCount++;
	if (compShips.at(i)->get_health() == 0)
	    playerCount++;
    }

    if (playerCount == 5) {
	cout << "Player has won!" << endl;
	return true;
    }

    if (compCount == 5) {
 	cout << "Player has lost!" << endl;
	return true;
    }

    return false;
}

void Game::print_guess(Factory* ptr) {
    if (ptr->getFactoryType() == "player")
    	print_board(guessBoard);
    else
	print_board(playerBoard);
}
