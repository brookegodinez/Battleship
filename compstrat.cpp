#include "compstrat.h"

string RandomGuess::computeStrategy(vector<string>& prev) {
    srand(time(NULL));
    vector<string> horizCoord = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    vector<string> vertCoord = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    string output = "";

    bool newCoords = false;
    while(newCoords == false){
        int pos = rand() % 10;
        output += horizCoord.at(pos);
        pos = rand() % 10;
        output += vertCoord.at(pos);
        int trackSame = 0;
        for(int i = 0; i < prev.size(); ++i){
            if(output == prev.at(i)){
                trackSame++;
            }
        }    
        if(trackSame == 0){
            newCoords = true;
        }  
        else{
            output = "";
        }   
    }
    cout << output << endl;
    return output;
}


string HorizontalGuess::computeStrategy(vector<string>& prev) {
    string horiz = prev.at(prev.size() - 1).substr(0, 1);
    string vert = prev.at(prev.size() - 1).substr(1, 1);
    string output, temp;
    string column = "ABCDEFGHIJ";
    srand(time(NULL));
    int numTimesThrough = 0;
    //if no viable squares, output random viable square
    start:
	int choice = rand() % 2;
	choice = choice*2 - 1;
	int colPos = column.find(horiz);
	int newColPos = colPos + choice;
	    
	if(newColPos < 0) {
	    newColPos = 2;
	}
	else if(newColPos > 9){
	    newColPos = 8;
	}
        
	output += column.at(newColPos);
	output += vert;

	if(repeatCoords(output, prev) == true) {
	    output = "";
	    numTimesThrough++;
   	    if(numTimesThrough < 100)
		goto start;
        }
// 	cout << "Attack Coord is: " << output << endl;
	return output;
    //if call is end case, do the proper case
    //to get new column, add choice to find
    //get letter by using find on the column
}

string VerticalGuess::computeStrategy(vector<string>& prev) {
    string horiz = prev.at(prev.size() - 1).substr(0, 1);
    string vert = prev.at(prev.size() - 1).substr(1, 1);
    string output, temp;
    vector<string> rows = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    srand(time(NULL));
    int numTimesThrough = 0;
    //if no viable squares, output random viable square
    start:
	int choice = rand() % 2;
	choice = choice*2 - 1;
	int rowPos;
        for(int i = 0; i < rows.size(); i++) {
            if(rows.at(i) == vert)
	        rowPos = i;
        }	
	int newRowPos = rowPos + choice;
	    
	if(newRowPos < 0) {
	    newRowPos = 2;
	}
	else if(newRowPos > 9){
	    newRowPos = 8;
	}
        
	output += horiz;
	output += rows.at(newRowPos);

	if(repeatCoords(output, prev) == true) {
	    output = "";
	    numTimesThrough++;
	    if(numTimesThrough < 100)
	        goto start;
 	    else
		return output;
        }
// 	cout << "Attack Coord is: " << output << endl;
	return output;
    //if call is end case, do the proper case
    //to get new column, add choice to find
    //get letter by using find on the column
}

bool CompStrat::repeatCoords(string coords, vector<string>& prev) {
    for(int i = 0; i < prev.size(); i++) {
	if(coords == prev.at(i)) {
	    return true;
        }
    }
    return false;  
}
