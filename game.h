#ifndef __GAME_H__
#define __GAME_H__

//#include "board.h"

#include "ship.h"
#include "factory.h"
#include <string>

using namespace std;

class Game {
    private:
	      //@brooke added
	      Factory* playerFactory = new PlayerShipFactory(); 
	      Factory* compFactory= new CompShipFactory();
	
        string playerBoard[10][10] = {
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"}};		
        string compBoard[10][10] = {
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"}};
 	string guessBoard[10][10] = {
	      {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"},
              {"0","0","0","0","0","0","0","0","0","0"}};	
        vector<Ship*> playerShips;
        vector<Ship*> compShips;
        //bool player_auto;
        vector<string> hit_record; //@BROOKE ADD
        bool correct_guess = false;

  public:
        vector<string> prev_guess_comp; //brooke
        vector<string> prev_guess;//@brooke

        ~Game();
        void print_board(string ships[][10]);		//prints blank board         
        void print_char(char c, int num);		//prints char num times
        void print_string(string str, int num);		//prints string num times
        void flush();					//clears termainal
        void color(string str, int num);		//outputs color to terminal

        void place_ships();				//inside factory.h
        void set_ship(Ship* ship, int length, string type, string ships[][10]);
        bool is_available(string ships[][10], int length, int x1, int x2, int y1, int y2);
        int convert_coord_row(string str);
        int convert_coord_col(string str);
        //playerAttack(&compShips);
        // is_blank_square();      //rename
        // is_sunk();              // is_destroyed();
        void player_attack(Factory* ptr, std::string coord, int strategy);
        //Game();
        Factory* get_player() {return playerFactory;}; //@brooke add
        Factory* get_auto(){ return compFactory;}; //@brooke
        void get_hit_record(){
          for (int g = 0; g < hit_record.size(); g++){
             cout << hit_record[g] << " ";} 
          cout << endl;
        } //BROOKE ADD
    	bool valid_square(string coord);
	bool winner();	
	void print_guess(Factory* ptr);
};

#endif // __GAME_H__
