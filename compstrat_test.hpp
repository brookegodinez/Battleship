#ifndef __COMPSTRAT_TEST_HPP__
#define __COMPSTRAT_TEST_HPP__

#include "compstrat.cpp"
#include "compstrat.h"
#include "gtest/gtest.h"

#include <vector>
#include <iostream>
#include <string>

TEST(RandomTest, CheckUpperBound) {
    RandomGuess random;
    vector<string> prev;
    string coord = random.computeStrategy(prev);
    EXPECT_TRUE(coord.substr(0, 1) <= "J");
    EXPECT_TRUE(stoi(coord.substr(1)) <= 10);
}

TEST(RandomTest, CheckLowerBound) {
    RandomGuess random;
    vector<string> prev;
    string coord = random.computeStrategy(prev);
    EXPECT_TRUE(coord.substr(0, 1) >= "A");
    EXPECT_TRUE(stoi(coord.substr(1)) >= 1);
}

TEST(RandomTest, CheckRepeat) {
    RandomGuess random;
    vector<string> prev = {"B3", "C8", "I9"};
    string coord = random.computeStrategy(prev);
    EXPECT_TRUE(coord != "B3");
    EXPECT_TRUE(coord != "C8");
    EXPECT_TRUE(coord != "I9");
}

TEST(HorizontalTest, CheckLeftRight) {
    HorizontalGuess horiz;
    vector<string> prev = {"G5"};
    string coord = horiz.computeStrategy(prev);
    EXPECT_TRUE(stoi(coord.substr(1)) == 5);
}

TEST(HorizontalTest, CheckLeft) {
    HorizontalGuess horiz;
    vector<string> prev = {"H5", "G5"};
    string coord = horiz.computeStrategy(prev);
    EXPECT_EQ(coord, "F5");
}

TEST(HorizontalTest, CheckRight) {
    HorizontalGuess horiz;
    vector<string> prev = {"F5", "G5"};
    string coord = horiz.computeStrategy(prev);
    EXPECT_EQ(coord, "H5");
}

TEST(HorizontalTest, NonePossible) {
    HorizontalGuess horiz;
    vector<string> prev = {"F5", "H5", "G5"};
    string coord = horiz.computeStrategy(prev);
    EXPECT_EQ(coord, "");
}

TEST(VerticalTest, CheckUpDown) {
    VerticalGuess vert;
    vector<string> prev = {"G5"};
    string coord = vert.computeStrategy(prev);
    EXPECT_EQ(coord.substr(0, 1), "G");
}

TEST(VerticalTest, CheckUp) {
    VerticalGuess vert;
    vector<string> prev = {"G6", "G5"};
    string coord = vert.computeStrategy(prev);
    EXPECT_EQ(coord, "G4");
}

TEST(VericalTest, CheckDown) {
    VerticalGuess vert;
    vector<string> prev = {"G4", "G5"};
    string coord = vert.computeStrategy(prev);
    EXPECT_EQ(coord, "G6");
}

TEST(VerticalTest, NonePossible) {
    VerticalGuess vert;
    vector<string> prev = {"G4", "G6", "G5"};
    string coord = vert.computeStrategy(prev);
    EXPECT_EQ(coord, "");
}

#endif
