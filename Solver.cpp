#include "Solver.h"

int Solver::minimax(bool isMaximizing, int depth, int alpha, int beta) {
    if (gameInstance.check_Winner('o')) { return 10 - depth; }  // CPU wins
    else if (gameInstance.check_Winner('x')) { return depth - 10; }  // Player wins
    else if (gameInstance.getNo_O() + gameInstance.getNo_X() == 9) { return 0 - depth;} // Draw

    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gameInstance.getMap(i, j) == ' ') {
                    gameInstance.input('o', i, j);               // Simulate 
                    int eval = minimax(false, depth + 1, alpha, beta);
                    gameInstance.input(' ', i, j);              // Undo 
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);                  // Update alpha
                    if (beta <= alpha) { return maxEval; }     // Prune
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gameInstance.getMap(i, j) == ' ') {
                    gameInstance.input('x', i, j);               // Simulate 
                    int eval = minimax(true, depth + 1, alpha, beta);
                    gameInstance.input(' ', i, j);              // Undo
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);                    // Update beta
                    if (beta <= alpha) { return minEval; }     // Prune
                }
            }
        }
        return minEval;
    }
}

pair<int, int> Solver::findBestMove() {
    int bestScore = INT_MIN;
    pair<int, int> bestMove = { -1, -1 };
    int alpha = INT_MIN, beta = INT_MAX;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameInstance.getMap(i, j) == ' ') {
                gameInstance.input('o', i, j);                   // Simulate 
                int moveScore = minimax(false, 0, alpha, beta); // Evaluate 
                gameInstance.input(' ', i, j);                 // Undo 

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = { i, j };
                }
            }
        }
    }

    return bestMove;
}

// Remeber these words  "Simulate, Evaluate, Undo" - Sun Tzu Art of Minimax