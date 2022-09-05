#include <iostream>
#include "game.h"
//#include "fillerPlayer.h"

using namespace std;

int alphabeta(int depth, int alpha, int beta, bool isMaximizingPlayer, Game* state) {
    if (depth == 0 || state->gameIsOver()) {
        return (state->playerOneProp->size()) - (state->playerTwoProp->size());
    }
    unordered_set<int> possibleMoves = state->generateMoves();
    if (isMaximizingPlayer) {
        int value = INT8_MIN;
        for (auto i : possibleMoves) {
            Game* copyState = new Game(state);
            copyState->makeMove(i, isMaximizingPlayer);
            value = max(value, alphabeta(depth - 1, alpha, beta, false, copyState));
            if (value >= beta) {
                break;
            }  
            alpha = max(alpha, value);
            delete copyState;
        }
        return value;
    } else {
        int value = INT8_MAX;
        for (auto i : possibleMoves) {
            Game* copyState = new Game(state);
            copyState->makeMove(i, isMaximizingPlayer);
            value = min(value, alphabeta(depth - 1 , alpha, beta, true, copyState));
            if (value <= alpha) {
                break;
            }
            beta = min(beta, value);
            delete copyState;
        }
        return value;
    }
}

int main() {
    const int DETPH = 1;
    cout << "Made 100% by Michael Mendoza and no one else Trademarked and patented\n";
    cout << "Welcome to Filler this shit gonna beat ur ass lmao\n";
    cout << "U tryna run your own board or nah? (y/n)\n";
    string random;
    cin >> random; 
    bool isRandom = (random == "n");
    Game* mainGame = new Game(isRandom);
    bool isPlayerOne;
    string playAI;
    cout << "Do you want to play against the AI? (y/n)\n";
    cin >> playAI;
    bool playingAI = (playAI == "y");
    isPlayerOne = !playingAI;
    
    while (!mainGame->gameIsOver()) {
        cout << "Current board is: \n";
        mainGame->printBoard();
        int color; 
        cout << "Which color u tryna pick\n";
        cout << "player one color: " << mainGame->playerOneColor;
        cout << endl << "player one property: ";
        for (auto i : *mainGame->playerOneProp) {
            cout << i << " ";
        }
        cout << "\n";
        cout << "player two color: " << mainGame->playerTwoColor;
        cout << endl << "player two property: ";
        for (auto i : *mainGame->playerTwoProp) {
            cout << i << " ";
        }
        cout << "\n";
        if (playingAI) {
            cout << "The AI is player 1, you are player 2\n";
            int bestMove = INT8_MIN; 
            int bestValue = INT8_MIN;
            for (auto i : mainGame->generateMoves()) {
                Game* copyState = new Game(mainGame);
                copyState->makeMove(i, true);
                int value = alphabeta(DETPH, INT8_MIN, INT8_MAX, true, copyState);
                if (value > bestValue) {
                    bestMove = i;
                    bestValue = value;
                }
                delete copyState;
            }
            cout << "Making move: ";
            cout << bestMove << "\n"; 
            mainGame->makeMove(bestMove, true);
            cout << "Current board is: \n";
            mainGame->printBoard();
            int color; 
            cout << "Which color u tryna pick\n";
            cout << "player one color: " << mainGame->playerOneColor;
            cout << endl << "player one property: ";
            for (auto i : *mainGame->playerOneProp) {
                cout << i << " ";
            }
            cout << "\n";
            cout << "player two color: " << mainGame->playerTwoColor;
            cout << endl << "player two property: ";
            for (auto i : *mainGame->playerTwoProp) {
                cout << i << " ";
            }
            cout << "\n";
        }
        cout << endl << "possible moves are: ";
        unordered_set<int> possibleMoves = mainGame->generateMoves();
        for (auto i : possibleMoves) {
            cout << i << " ";
        }
        cout << endl;
        cin >> color; 
        
        while (possibleMoves.find(color) == possibleMoves.end()){
            cout << "You did not enter a valid move! Try again bruh\n";
            cin >> color;
        }
        
        mainGame->makeMove(color, isPlayerOne);
        if (!playingAI) {
            isPlayerOne = !isPlayerOne;
        }
        
    }
    cout << "Game Over! The winner is player: ";
    cout << mainGame->getWinner();
    cout << "\n";
    return 0;
}
