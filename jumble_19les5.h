//
// Created by Lauren Steel on 11/3/22.
// 20218337
// Assignment 3
// Nov 14 2022
//

#pragma once
#include <string>
using namespace std;

// exception class
class BadJumbleException {
public:
        BadJumbleException(const string&);
        string& what();
private:
        string message;
};

// setting the type of the 2D array of char will be charArrayPtr*
typedef char* charArrayPtr;

class JumblePuzzle {
public:
    // jumblePuzzle class
    JumblePuzzle (const string&, const string&);
    // copy constructor
    JumblePuzzle(const JumblePuzzle&);
    // accessors
    char getDirection() const;
    int getDifficulty() const;
    int getSize() const;
    int getRowPos() const;
    int getColPos() const;
    charArrayPtr* getJumble() const;
    // destructor
    ~JumblePuzzle();
    // overload the assignment
    JumblePuzzle& operator=(const JumblePuzzle&);
private:
    // private members
    char direction;
    int level;
    int size;
    int rowPosition;
    int colPosition;
    string hiddenWord;
    charArrayPtr* jumbleBoard;
    charArrayPtr* copyArray(const charArrayPtr*, const int) const;
    void deleteJumble();
    int getRand(int);
    void createJumble();
};

