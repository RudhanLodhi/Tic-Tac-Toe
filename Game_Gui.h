#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "TicTacToe.h"
#include <vector>
using namespace std;
using namespace sf;

class Game_Gui {
private:
    TicTacToe game;
public:
    Game_Gui();
    void DrawGrid(RenderWindow& window);
    void DrawCross(RenderWindow& window, float col, float row);
    void DrawCircle(RenderWindow& window, float col, float row);
    void DrawScore(RenderWindow& window);
    void DrawStartMenu(RenderWindow& window);
    int DisplayStartMenu(RenderWindow& window);


    int HandleStartMenuInput(RenderWindow& window);
    vector<string> GetPlayerNames(RenderWindow& window);

    void Clicksound();
    void showMessageBox(RenderWindow& window, string& resultMessage);
    pair<string, string> InputPlayerNames(RenderWindow& window, bool isPvP);
   
    string game_end();
    vector<int> HandleInput(RenderWindow& window);
    void MenuText(RenderWindow& window, bool turn = false);
    TicTacToe& getGame() { return game; }
};
