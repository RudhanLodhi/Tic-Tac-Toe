#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "TicTacToe.h"
#include <vector>
using namespace std;

class Game_Gui {
private:
    TicTacToe game;
public:
    Game_Gui();
    void DrawGrid(sf::RenderWindow& window);
    void DrawCross(sf::RenderWindow& window, float col, float row);
    void DrawCircle(sf::RenderWindow& window, float col, float row);
    void DrawScore(sf::RenderWindow& window);

    void Clicksound();
    void showMessageBox(sf::RenderWindow& window);
    
    bool game_end();
    vector<int> HandleInput(sf::RenderWindow& window);
    void MenuText(sf::RenderWindow& window, bool turn = false);
    TicTacToe& getGame() { return game; }
};
