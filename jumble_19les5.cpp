//
// Created by Lauren Steel on 11/3/22.
// 20218337
// Assignment 3
// Nov 14 2022
//

#include <string>
#include <cstdlib>
#include <ctime>
#include "jumble_19les5.h"

using namespace std;

// exceptions are thrown when bad user input is received
BadJumbleException::BadJumbleException(const string& m) : message(m) {}
string& BadJumbleException::what() {
    return message;
}

// jumblePuzzle constructor
JumblePuzzle::JumblePuzzle(const string& word, const string& difficulty) : hiddenWord(word) {
    int wordLen = word.size();
    // exception thrown if the length of the word is too long or too short
    if (wordLen < 3)
        throw BadJumbleException("Given word must be at least 3 characters long");
    if (wordLen > 10)
        throw BadJumbleException("Given word can only be up to 10 characters long");

    // the word is an appropriate length
    char levelSelect = difficulty.at(0);
    if (levelSelect == 'E' || levelSelect == 'e')
        level = 2;
    else if (levelSelect == 'M' || levelSelect == 'm')
        level = 3;
    else if (levelSelect == 'H' || levelSelect == 'h')
        level = 4;
    else
        // exception thrown if a non-existent difficulty level is specified
        throw BadJumbleException("Non existent level");

    size = wordLen * level;
    jumbleBoard = new charArrayPtr[size];
    for (int i = 0; i < size; i++)
        jumbleBoard[i] = new char[size];

    int seed = static_cast<int>(time(nullptr));
    srand(seed);

    createJumble();
} // end constructor

// jumblePuzzle copy constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp) {
    size = jp.getSize();
    jumbleBoard = copyArray(jp.getJumble(), size);
    level = jp.getDifficulty();
    direction = jp.getDirection();
    rowPosition = jp.getRowPos();
    colPosition= jp.getColPos();
    hiddenWord = string(jp.hiddenWord);
} // end copy constructor

// accessors
int JumblePuzzle::getSize() const { return size; }

charArrayPtr* JumblePuzzle::getJumble() const {
    return copyArray(jumbleBoard, size);
}
int JumblePuzzle::getDifficulty() const { return level; }

char JumblePuzzle::getDirection() const { return direction; }

int JumblePuzzle::getRowPos() const { return rowPosition; }

int JumblePuzzle::getColPos() const { return colPosition; }
// end accessors

// destructor
JumblePuzzle::~JumblePuzzle() {
    deleteJumble();
}// end destructor

// deleteJumble
void JumblePuzzle::deleteJumble() {
    for (int i = 0; i < size; i++)
        delete[] jumbleBoard[i];
    delete[] jumbleBoard;
    jumbleBoard = nullptr;
} // end deleteJumble

// jumblePuzzle overload the assignment operator
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& jp) {
    if (this != &jp) {
        deleteJumble();
        size = jp.getSize();
        jumbleBoard = copyArray(jp.getJumble(), jp.getSize());
    }
    return *this;
} // end operator

// copyArray
charArrayPtr* JumblePuzzle::copyArray(const charArrayPtr* anotherJumble, const int anotherSize) const {
    int sz = anotherSize;
    int j, k;
    charArrayPtr* newPuzzle = new charArrayPtr[sz];
    for (j = 0; j < sz; j++)
        newPuzzle[j] = new char[sz];
    for (j = 0; j < sz; j++)
        for (k = 0; k < sz; k++)
            newPuzzle[j][k] = anotherJumble[j][k];
    return newPuzzle;
} // end copyArray

// getRand
int JumblePuzzle::getRand(int max) { return rand() % max; }

// createJumble
void JumblePuzzle::createJumble() {
    // variable set up
    int row, column, letterLocation;
    int wordSize = size / level;
    bool spotWorks;

    // choosing a random direction from the string "nesw"
    // orientation can only be horizontal or vertical
    string orientations("nesw");
    for (row = 0; row < size; row++)
        for (column = 0; column < size; column++) {
            // generating random letter from the alphabet
            jumbleBoard[row][column] = 97 + getRand(26);
        }

    // generating random location
    rowPosition = getRand(size-1);
    colPosition = getRand(size-1);
    jumbleBoard[rowPosition][colPosition] = hiddenWord.at(0);

    /* setting the word at any random position at a random orientation (north, east, south or west)
     * if the word is within the dimensions of the 'board' at the spot specified then spotWorks is true
     * and wordLocation is set if not another orientation is attempted
     * there is at least a 50% chance of getting a direction in which the word will fit
     * (not too many orientations should need to be attempted)
     * Just leave the letters from the partial word in the puzzle - just to make it more fun! */
    do {
        spotWorks = true;
        letterLocation = 1;
        direction = orientations.at(getRand(4));
        if (direction == 'n') {
            row = rowPosition - 1;
            while (row >= 0 && letterLocation < wordSize) {
                jumbleBoard[row][colPosition] = hiddenWord.at(letterLocation);
                row--;
                letterLocation++;
            }
        }
        else if (direction == 'e') {
            column = colPosition + 1;
            while (column < size && letterLocation < wordSize) {
                jumbleBoard[rowPosition][column] = hiddenWord.at(letterLocation);
                column++;
                letterLocation++;
            }
        }
        else if (direction == 's') {
            row = rowPosition + 1;
            while (row < size && letterLocation < wordSize) {
                jumbleBoard[row][colPosition] = hiddenWord.at(letterLocation);
                row++;
                letterLocation++;
            }
        }
        else {
            column = colPosition - 1;
            while (column >= 0 && letterLocation < wordSize) {
                jumbleBoard[rowPosition][column] = hiddenWord.at(letterLocation);
                column--;
                letterLocation++;
            }
        }
        if (letterLocation < wordSize)
            spotWorks = false;
    } while(!spotWorks);
} // end createJumble
