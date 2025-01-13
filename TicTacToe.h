#pragma once
#include <string>
#define TIC_TAC_TOE
using namespace std;

class TicTacToe
{
	char map[3][3];
	int no_x;
	int no_o;
	int score[2]; // [0] = p1
	string P1Name;
	string P2name;
public:
	TicTacToe();
	void input(char p, int row, int col); // p is player (1 or 2)
	bool check_Winner(char ch); // ch is either x,o
	int getNo_X();
	int getNo_O();
	char getMap(int i, int j); // return desired element
	int getScore(char p); // x,o
	void updateScore(char p); // x,o
	void resetGame();
	void setP1Name(string x);
	void setP2Name(string x);
	string getP1Name();
	string getP2Name();
};
