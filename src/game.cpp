#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_set>
#include "game.h"
#include <ctime>

using namespace std;    

Game::Game(bool isRandom) {
    this->playerOneProp = new unordered_set<int>;
    this->playerTwoProp = new unordered_set<int>;
    board = new int[BOARD_SIZE * BOARD_SIZE];
    this->colors = new vector<int>;
    for (int i = 0; i < NUM_OF_COLORS; i++) {
        colors->push_back(i);
    }

    if (isRandom) {
        // for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        //     board[i] = -1;
        // }
        srand(time(0));
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
    playerOneProp->insert((BOARD_SIZE * BOARD_SIZE) - (BOARD_SIZE));
    //add top right to the plyerTwoProp list
    playerTwoProp->insert(BOARD_SIZE - 1);

    playerOneColor = board[(BOARD_SIZE * BOARD_SIZE) - (BOARD_SIZE)];
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

void Game::makeMove(int color, bool isPlayerOne) {
    unordered_set<int>* desiredProp;
    if (isPlayerOne) {
        desiredProp = playerOneProp;
        playerOneColor = color;
    } else {
        desiredProp = playerTwoProp;
        playerTwoColor = color;
    } 

    unordered_set<int> values;
    for (int8_t i : *desiredProp) {
        //top
        if (i - BOARD_SIZE > 0) {
            if (board[i - BOARD_SIZE] == color) {
                values.insert(i - BOARD_SIZE);
            }
        }
        //bottom
        if (i + BOARD_SIZE < (BOARD_SIZE * BOARD_SIZE)) {
            if (board[i + BOARD_SIZE] == color) {
                values.insert(i + BOARD_SIZE);
            }
        }
        //left
        if (((i - 1) / BOARD_SIZE) == (i / BOARD_SIZE) && (i - 1 >= 0)) {
            if (board[i - 1] == color) {
                values.insert(i - 1);
            }
        }
        //right
        if (((i + 1) / BOARD_SIZE) == (i / BOARD_SIZE) && i < BOARD_SIZE * BOARD_SIZE) {
            if (board[i + 1] == color) {
                values.insert(i + 1);
            }
        }
    }

    for (int8_t i : values) {
        desiredProp->insert(i);
    }

    for (int8_t i : *desiredProp) {
        board[i] = color;
    }
}    

unordered_set<int> Game::generateMoves() {
    //return all integers in COLOR except playerOneColor and playerTwoColor
    unordered_set<int> moves;
    for (int i = 0; i < NUM_OF_COLORS; i++) {
        if (i != playerOneColor && i != playerTwoColor) {
            moves.insert(i);
        }
    }
    return moves;
}

// unordered_set<int> Game::generateColors(int i) {
//     //return set of colors that are possible to place on the board
//     vector<int> colors;
//     for (int i = 0; i < NUM_OF_COLORS; i++) {
//         colors.push_back(i);
//     }

//     //top
//     if (i - BOARD_SIZE > 0) {
//         if (board[i - BOARD_SIZE] == color) {
//             values.insert(i - BOARD_SIZE);
//         }
//     }
//     //bottom
//     if (i + BOARD_SIZE < (BOARD_SIZE * BOARD_SIZE)) {
//         if (board[i + BOARD_SIZE] == color) {
//             values.insert(i + BOARD_SIZE);
//         }
//     }
//     //left
//     if (((i - 1) / BOARD_SIZE) == (i / BOARD_SIZE) && (i - 1 >= 0)) {
//         if (board[i - 1] == color) {
//             values.insert(i - 1);
//         }
//     }
//     //right
//     if (((i + 1) / BOARD_SIZE) == (i / BOARD_SIZE) && i < BOARD_SIZE * BOARD_SIZE) {
//         if (board[i + 1] == color) {
//             values.insert(i + 1);
//         }
//     }

//     return moves;
// }

void Game::printBoard() {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (i % BOARD_SIZE == 0) {
            cout << "\n";
        }
        cout << board[i] << " ";
    }
    cout << "\n";
}
