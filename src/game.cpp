#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_set>
#include "game.h"
#include <ctime>

using namespace std;    

Game::Game(bool isRandom) {
    //this->playerOneProp = new unordered_set<int>;
    //this->playerTwoProp = new unordered_set<int>;
    //this->colors = new vector<int>;
    for (int i = 0; i < NUM_OF_COLORS; i++) {
        colors.push_back(i);
    }

    if (isRandom) {
        // for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
        //     board[i] = -1;
        // }
        srand(time(0));
        for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
            board[i] = rand() % (NUM_OF_COLORS);
        }
    } else {
        cout << "Input colors (0-" << NUM_OF_COLORS - 1 << ")" << endl;
        cout << "-----------------------" << endl;
        for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
            cout << "(" << i / BOARD_HEIGHT << "," << i % BOARD_WIDTH << "): ";
            cin >> board[i];
        }
    }

    //add bottom left to the playerOneProp list
    playerOneProp.insert((BOARD_WIDTH * BOARD_HEIGHT) - (BOARD_WIDTH));
    //add top right to the plyerTwoProp list
    playerTwoProp.insert(BOARD_WIDTH - 1);

    playerOneColor = board[(BOARD_WIDTH * BOARD_HEIGHT) - (BOARD_WIDTH)];
    playerTwoColor = board[BOARD_WIDTH - 1];
    
}

bool Game::gameIsOver() {
    return (playerOneProp.size() + playerTwoProp.size() == (BOARD_WIDTH * BOARD_HEIGHT));
}

Game::Game(const Game& rhs) {
    playerOneProp = rhs.playerOneProp;
    playerTwoProp = rhs.playerTwoProp;
    playerOneColor = rhs.playerOneColor;
    playerTwoColor = rhs.playerTwoColor;
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
        board[i] = rhs.board[i];
    }
    colors = rhs.colors;
}

Game::~Game() {
    //delete[] board;
}

int Game::getWinner() {
    if (gameIsOver()) {
        if (playerOneProp.size() > playerTwoProp.size()) {
            return 1;
        } else {
            return 2;
        }
    }
    return 0;
}

void Game::makeMove(int color, bool isPlayerOne) {
    unordered_set<int> desiredProp;
    if (isPlayerOne) {
        desiredProp = playerOneProp;
        playerOneColor = color;
    } else {
        desiredProp = playerTwoProp;
        playerTwoColor = color;
    } 

    unordered_set<int> values;

    //loop through the desiredProp list and add all the neighbors that are the same color to the values list
    for (int i : desiredProp) {
        //check the top neighbor
        if (i - BOARD_WIDTH >= 0 && board[i - BOARD_WIDTH] == color) {
            values.insert(i - BOARD_WIDTH);
        }
        //check the bottom neighbor
        if (i + BOARD_WIDTH < BOARD_WIDTH * BOARD_HEIGHT && board[i + BOARD_WIDTH] == color) {
            values.insert(i + BOARD_WIDTH);
        }
        //check the left neighbor
        if (i % BOARD_WIDTH != 0 && board[i - 1] == color) {
            values.insert(i - 1);
        }
        //check the right neighbor
        if ((i + 1) % BOARD_WIDTH != 0 && board[i + 1] == color) {
            values.insert(i + 1);
        }
    }

    for (int8_t i : values) {
        desiredProp.insert(i);
    }

    for (int8_t i : desiredProp) {
        board[i] = color;
    }
    
    if (isPlayerOne) {
        playerOneProp = desiredProp;
    } else {
        playerTwoProp = desiredProp;
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
//     if (i + BOARD_SIZE < (BOARD_WIDTH * BOARD_HEIGHT)) {
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
//     if (((i + 1) / BOARD_SIZE) == (i / BOARD_SIZE) && i < BOARD_WIDTH * BOARD_HEIGHT) {
//         if (board[i + 1] == color) {
//             values.insert(i + 1);
//         }
//     }

//     return moves;
// }

void Game::printBoard() {
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
        if (i % BOARD_WIDTH == 0) {
            cout << "\n";
        }
        cout << board[i] << " ";
    }
    cout << "\n";
}
