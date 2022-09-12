#include <iostream>
#include "game.h"
//#include "fillerPlayer.h"

using namespace std;

//MiniMax with alpha beta pruning


int alphabeta(int depth, int alpha, int beta, bool isMaximizingPlayer, Game state) {
    if (depth == 0 || state.gameIsOver()) {
        return (state.playerOneProp.size()) - (state.playerTwoProp.size());
    }
    unordered_set<int> possibleMoves = state.generateMoves();
    if (isMaximizingPlayer) {
        int value = INT8_MIN;
        for (auto i : possibleMoves) {
            Game copyState = Game(state);
            copyState.makeMove(i, isMaximizingPlayer);
            value = max(value, alphabeta(depth - 1, alpha, beta, false, copyState));
            if (value >= beta) {
                break;
            }  
            alpha = max(alpha, value);
            //delete copyState;
        }
        return value;
    } else {
        int value = INT8_MAX;
        for (auto i : possibleMoves) {
            Game copyState = Game(state);
            copyState.makeMove(i, isMaximizingPlayer);
            value = min(value, alphabeta(depth - 1 , alpha, beta, true, copyState));
            if (value <= alpha) {
                break;
            }
            beta = min(beta, value);
            //delete copyState;
        }
        return value;
    }
}

int main() {
    //0 1 0 2 3 4 1 2 1 3 4 0 2 1 3 5 3 4 5 2 0 2 0 3 1 5 1 5 2 1 3 4 0 1 4 0 1 0 2 5 2 4 0 1 3 1 4 3 4 5 4 0 2 4 1 4
    const int DETPH = 1;
    cout << "Made 100% by GitHub Copilot and no one else Trademarked and patented\n";
    cout << "Welcome to Filler this shit gonna beat ur ass lmao\n";
    cout << "U tryna run your own board or nah? (y/n)\n";
    string random;
    cin >> random; 
    bool isRandom = (random == "n");
    Game mainGame = Game(isRandom);
    bool isPlayerOne;
    string playAI;
    cout << "You wanna to get folded by AI? (y/n)\n";
    cin >> playAI;
    bool playingAI = (playAI == "y");
    isPlayerOne = !playingAI;
    
    while (!mainGame.gameIsOver()) {
        cout << "Current board is: \n";
        mainGame.printBoard();
        int color; 
        cout << "Which color u tryna pick\n";
        cout << "player one color: " << mainGame.playerOneColor;
        cout << endl << "player one property: ";
        for (auto i : mainGame.playerOneProp) {
            cout << i << " ";
        }
        cout << "\n";
        cout << "player two color: " << mainGame.playerTwoColor;
        cout << endl << "player two property: ";
        for (auto i : mainGame.playerTwoProp) {
            cout << i << " ";
        }
        cout << "\n";
        if (playingAI) {
            cout << "The AI is player 1, you are player 2\n";
            int bestMove = INT8_MIN; 
            int bestValue = INT8_MIN;
            for (auto i : mainGame.generateMoves()) {
                Game copyState = Game(mainGame);
                copyState.makeMove(i, true);
                int value = alphabeta(DETPH, INT8_MIN, INT8_MAX, true, copyState);
                if (value > bestValue) {
                    bestMove = i;
                    bestValue = value;
                }
                //delete &copyState;
            }
            cout << "Making move: ";
            cout << bestMove << "\n"; 
            mainGame.makeMove(bestMove, true);
            cout << "------------------------------------\n";
            cout << "Current board is: \n";
            mainGame.printBoard();
            int color; 
            cout << "Which color u tryna pick\n";
            cout << "player one color: " << mainGame.playerOneColor;
            cout << endl << "player one property: ";
            for (auto i : mainGame.playerOneProp) {
                cout << i << " ";
            }
            cout << "\n";
            cout << "player two color: " << mainGame.playerTwoColor;
            cout << endl << "player two property: ";
            for (auto i : mainGame.playerTwoProp) {
                cout << i << " ";
            }
            cout << "\n";
        }
        cout << endl << "Possible moves are: ";
        unordered_set<int> possibleMoves = mainGame.generateMoves();
        for (auto i : possibleMoves) {
            cout << i << " ";
        }
        cout << endl;
        cin >> color; 
        
        while (possibleMoves.find(color) == possibleMoves.end()){
            cout << "You tweaking, invalid move! Try again bruh\n";
            cin >> color;
        }
        
        mainGame.makeMove(color, isPlayerOne);
        if (!playingAI) {
            isPlayerOne = !isPlayerOne;
        }
        
    }
    cout << "GGs. Loser got clapped by Player ";
    cout << mainGame.getWinner();
    cout << "\n";
    return 0;
}
