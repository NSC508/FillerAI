#include <iostream>
#include "game.h"
//#include "fillerPlayer.h"

using namespace std;

int alphabeta(int depth, int alpha, int beta, bool isMaximizingPlayer, Game* state) {
    if (depth == 0 || state->gameIsOver()) {
        if (isMaximizingPlayer) {
            return state->playerOneProp->size();
        } else {
            return state->playerTwoProp->size();
        }
    }
    vector<int>* possibleMoves = state->generateMoves();
    if (isMaximizingPlayer) {
        int value = INT8_MIN;
        for (auto &i: *possibleMoves) {
            Game* copyState = new Game(state);
            copyState->makeMove(i, isMaximizingPlayer);
            int alphaBeta = alphabeta(depth - 1, alpha, beta, false, copyState);
            if (alphaBeta > value) {
                value = alphaBeta;
            }
            if (value >= beta) {
                break;
            } 
            alpha = max(alpha, value);
            delete copyState;
        }
        return value;
    } else {
        int value = INT8_MAX;
        for (auto &i: *possibleMoves) {
            Game* copyState = new Game(state);
            copyState->makeMove(i, isMaximizingPlayer);
            int alphaBeta = alphabeta(depth - 1 , alpha, beta, true, copyState);
            if (alphaBeta < value) {
                value = alphaBeta;
            }
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
    const int DETPH = 2;
    cout << "Made 100% by Michael Mendoza and no one else Trademarked and patented\n";
    cout << "Welcome to Filler this shit gonna beat ur ass lmao\n";
    cout << "U tryna run your own board or nah? (y/n)\n";
    string random;
    cin >> random; 
    bool isRandom = (random == "n");
    Game* mainGame = new Game(isRandom);
    bool isPlayerOne = true;
    string playAI;
    cout << "Do you want to play against the AI? (y/n)\n";
    cin >> playAI;
    bool playingAI = (playAI == "y");
    while (!mainGame->gameIsOver()) {
        cout << "Current board is: \n";
        mainGame->printBoard();
        int color; 
        cout << "Which color u tryna pick\n";
        cin >> color; 
        vector<int>* possibleMoves = mainGame->generateMoves();
        // while (find(possibleMoves->begin(), possibleMoves->end(), color) != possibleMoves->end()){
        //     cout << "You did not enter a valid move! Try again bruh";
        //     cin >> color;
        // }
        mainGame->makeMove(color, isPlayerOne);
        if (playingAI) {
            int bestMove = INT8_MIN; 
            int bestValue = INT8_MIN;
            for (auto &i : *mainGame->generateMoves()) {
                Game* copyState = new Game(mainGame);
                int value = alphabeta(DETPH, INT8_MIN, INT8_MAX, false, copyState);
                if (value > bestValue) {
                    bestMove = i;
                    bestValue = value;
                }
                delete copyState;
            }
            cout << "Making move: ";
            cout << bestMove; 
            mainGame->makeMove(bestMove, false);
        } else {
            isPlayerOne = !isPlayerOne;
        }
    }
    cout << "Game Over! The winner is player: ";
    cout << mainGame->getWinner();
    return 0;
}
