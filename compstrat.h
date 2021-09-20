#ifndef __COMPSTRAT_H__
#define __COMPSTRAT_H__

using namespace std;
#include <string>
#include <vector>
#include <stdlib.h>
#include "compstrat.h"
#include <iostream>
#include <ctime>

class CompStrat {
    public:
        virtual ~CompStrat() { }
        virtual string computeStrategy(vector<string>&) = 0; //returns coordinate pair 
	//other strats: edges, corners
    protected: 
	bool repeatCoords(string, vector<string>&);
};

class Context {
    private:
        CompStrat* strategy_ = nullptr;
  
    public:
        Context(CompStrat* strategy) {
	    this->strategy_ = strategy;
	}
        ~Context(){
	    delete this->strategy_;
	}
        void setStrategy(CompStrat* strategy) {
	    delete this->strategy_;
	    this->strategy_ = strategy;
	}
	string useStrategy(vector<string>& prev) { //changed to return string
	    return this->strategy_->computeStrategy(prev);
	}
};

class RandomGuess : public CompStrat { //guessing randomly
    public:
	/*virtual*/
        std::string computeStrategy(vector<string>& prev);
};

class VerticalGuess : public CompStrat {
    public:
	std::string computeStrategy(vector<string>& prev);
};

class HorizontalGuess : public CompStrat {
    public:
	std::string computeStrategy(vector<string>& prev);
};

#endif // __COMPSTRAT_H__
