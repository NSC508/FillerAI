#ifndef GAME_H
#define GAME_H

#include <vector>
#include <unordered_set>

using namespace std;

class Game {
    public: 
        //const int BOARD_SIZE = 8;
        const static int BOARD_WIDTH = 8;
        const static int BOARD_HEIGHT = 7;
        const int NUM_OF_COLORS = 6;
        // Black, Red, Purple, Green, Blue, Yellow

        unordered_set<int> playerOneProp; 
        unordered_set<int> playerTwoProp;
        int playerOneColor;
        int playerTwoColor;

        int board[BOARD_WIDTH * BOARD_HEIGHT];
        vector<int> colors;
        
        Game(bool isRandom);
        
        Game(const Game& rhs);

        ~Game();

        bool gameIsOver();

        int getWinner();

        // int* score();

        void makeMove(int color, bool isPlayerOne);   

        unordered_set<int> generateMoves();
        //unordered_set<int> generateColors(int i);

        void printBoard();
};

#endif
