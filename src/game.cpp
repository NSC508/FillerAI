#include <iostream>
#include <vector>
#include <math.h>
#include "game.h"

using namespace std;    

Game::Game(bool isRandom) {
    this->playerOneProp = new vector<int>;
    this->playerTwoProp = new vector<int>;
    board = new int[BOARD_SIZE * BOARD_SIZE];
    this->colors = new vector<int>;
    for (int i = 0; i < NUM_OF_COLORS; i++) {
        colors->push_back(i);
    }

    if (isRandom) {
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            board[i] = rand() % (NUM_OF_COLORS);
        }
    } else {
        cout << "Input colors (0-" << NUM_OF_COLORS - 1 << ")" << endl;
        cout << "-----------------------" << endl;
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            cout << "(" << i % BOARD_SIZE << "," << i / BOARD_SIZE << "): ";
            cin >> board[i];
        }
    }

    //add bottom left to the playerOneProp list
    playerOneProp->push_back((BOARD_SIZE * (BOARD_SIZE - 1)) - 1);
    //add top right to the plyerTwoProp list
    playerTwoProp->push_back(BOARD_SIZE - 1);

    playerOneColor = board[(BOARD_SIZE * (BOARD_SIZE - 1)) - 1];
    playerTwoColor = board[BOARD_SIZE - 1];
    
}

bool Game::gameIsOver() {
    return (this->playerOneProp->size() + this->playerTwoProp->size() == (BOARD_SIZE * BOARD_SIZE));
}

Game::Game(const Game &rhs) {
    this->playerOneProp = rhs.playerOneProp;
    this->playerTwoProp = rhs.playerTwoProp;
    this->playerOneColor = rhs.playerOneColor;
    this->playerTwoColor = rhs.playerTwoColor;
    this->board = rhs.board;
    this->colors = rhs.colors;
}

Game::~Game() {
    delete playerOneProp;
    delete playerTwoProp;
    delete board;
    delete colors;

    playerOneProp = nullptr;
    playerTwoProp = nullptr;
    board = nullptr;
    colors = nullptr;
}

int Game::getWinner() {
    if (gameIsOver()) {
        if (this->playerOneProp->size() > this->playerTwoProp->size()) {
            return 1;
        } else {
            return 2;
        }
    }
    return 0;
}

// int* Game::score() {
//     int score[] = {this->playerOneProp->size(), this->playerTwoProp->size()};
//     return score;
// }

void Game::makeMove(int color, bool isPlayerOne) {
    vector<int>* desiredProp;
    if (isPlayerOne) {
        desiredProp = this->playerOneProp;
        playerOneColor = color;
    } else {
        desiredProp = this->playerTwoProp;   
        playerTwoColor = color;
    } 

    for (auto &i : *desiredProp) {
        //top
        if (i - BOARD_SIZE > 0) {
            if (board[i - BOARD_SIZE] == color) {
                desiredProp->push_back(i - BOARD_SIZE);
            }
        }
        //bottom
        if (i + BOARD_SIZE < (BOARD_SIZE * BOARD_SIZE)) {
            if (board[i + BOARD_SIZE] == color) {
                desiredProp->push_back(i + BOARD_SIZE);
            }
        }
        //left
        if (((i - 1) / BOARD_SIZE) != (i / BOARD_SIZE)) {
            if (board[i - 1] == color) {
                desiredProp->push_back(i - 1);
            }
        }
        //right
        if (((i + 1) / BOARD_SIZE) != (i / BOARD_SIZE)) {
            if (board[i + 1] == color) {
                desiredProp->push_back(i + 1);
            }
        }

        i = color;
    }
}    

vector<int>* Game::generateMoves() {
    //return all integers in COLOR except playerOneColor and playerTwoColor
    vector<int>* moves = new vector<int>;
    for (int i = 0; i < NUM_OF_COLORS; i++) {
        moves->push_back(i);
    }
    vector<int>::iterator it;
    it = moves->begin() + playerOneColor;
    moves->erase(it);

    it = moves->begin() + playerTwoColor;
    moves->erase(it);

    return moves;
}

void Game::printBoard() {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (i % BOARD_SIZE == 0) {
            cout << "\n";
        }
        cout << board[i] << " ";
    }
    cout << "\n";
}
