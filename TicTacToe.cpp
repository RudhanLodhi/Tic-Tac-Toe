#include "TicTacToe.h"
#include <string>

TicTacToe::TicTacToe() : P1Name("Player 1") , P2name("Player 2")
{
    score[0] = 0;
    score[1] = 0;
    resetGame();
}

void TicTacToe::input(char p, int row, int col) // p = player (either x,o)
{
	if (row >=3 || col >= 3 || row<0 || col<0 || map[row][col] == 'x' || map[row][col] == 'o') // possible error conditions
	{
		return;
	}
	if (p == 'x'){
		map[row][col] = 'x';
        no_x++;
	}
	else{
		map[row][col] = 'o';
        no_o++;
	}
}

bool TicTacToe::check_Winner(char ch)
{
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (map[i][0] == ch && map[i][1] == ch && map[i][2] == ch) {
            return true;
        }
    }
    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (map[0][j] == ch && map[1][j] == ch && map[2][j] == ch) {
            return true;
        }
    }
    // Check diagonals
    if (map[0][0] == ch && map[1][1] == ch && map[2][2] == ch) {
        return true;
    }
    if (map[0][2] == ch && map[1][1] == ch && map[2][0] == ch) {
        return true;
    }
    return false;
}

int TicTacToe::getNo_X()
{
    return no_x;
}

int TicTacToe::getNo_O()
{
    return no_o;
}

char TicTacToe::getMap(int i , int j)
{
    return map[i][j];
}

int TicTacToe::getScore(char p) { return (p == 'x' ? score[0] : score[1]); }

void TicTacToe::updateScore(char p) { (p == 'x' ? score[0]++ : score[1]++);}

void TicTacToe::resetGame()
{
    no_o = 0;
    no_x = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) 
        {
            map[i][j] = ' ';
        }
    }
}

void TicTacToe::setP1Name(string &x) { P1Name = x; }
void TicTacToe::setP2Name(string &x) { P2name = x; }

string TicTacToe::getP1Name() { return P1Name;}
string TicTacToe::getP2Name() { return P2name;}