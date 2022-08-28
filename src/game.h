#ifndef GAME_H
#define GAME_H

#include <vector>

using namespace std;

class Game {
    public: 
        const int BOARD_SIZE = 8;
        const int NUM_OF_COLORS = 6;
        // Black, Red, Purple, Green, Blue, Yellow

        vector<int>* playerOneProp; 
        vector<int>* playerTwoProp;
        int playerOneColor;
        int playerTwoColor;
        int* board;
        vector<int>* colors;
        
        Game(bool isRandom);
        
        Game(const Game &rhs);

        ~Game();

        bool gameIsOver();

        int getWinner();

        int* score();

        void makeMove(int color, bool isPlayerOne);   

        vector<int>* generateMoves();

        void printBoard();
};

#endif
