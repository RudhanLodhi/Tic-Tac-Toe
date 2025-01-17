#pragma once
#ifndef SOLVER_H
#define SOLVER_H

#include "TicTacToe.h"
#include <limits.h> 
using namespace std;

class Solver {
public:
    Solver(TicTacToe& game) : gameInstance(game) {}
    pair<int, int> findBestMove();

private:
    TicTacToe& gameInstance;
    int minimax(bool isMaximizing, int depth, int alpha, int beta);
};

#endif