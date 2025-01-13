#include "Game_Gui.h"
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;

int main() {
    RenderWindow window(VideoMode(700, 800), "Tic-Tac-Toe");
    Game_Gui gui;

    int mode = gui.DisplayStartMenu(window);
    if (mode == -1) {
        return 0;
    }

    if (mode == 1) { // Player vs Player
        pair<string, string> playerNames = gui.InputPlayerNames(window, true);
        gui.getGame().setP1Name(playerNames.first);
        gui.getGame().setP2Name(playerNames.second);
    }
    else if (mode == 2) { // Player vs CPU
        pair<string, string> playerNames = gui.InputPlayerNames(window, false);
        gui.getGame().setP1Name(playerNames.first);
        gui.getGame().setP2Name(playerNames.second);
    }

    bool turn = rand() % 2;

    // Main game loop
    while (window.isOpen()) {
        window.clear(Color::Black);

        gui.DrawGrid(window);
        gui.MenuText(window, turn);
        gui.DrawScore(window);

        vector<int> cords = gui.HandleInput(window);
        if (cords[0] != -1 && cords[1] != -1) {
            if (!turn) { // Player 1's turn
                gui.getGame().input('x', cords[0], cords[1]);
                    turn = true;
            }
            else { // Player 2 or CPU's turn
                if (mode == 1) { // Player vs Player
                    gui.getGame().input('o', cords[0], cords[1]);
                        turn = false;
                }
                //else if (mode == 2) { // Player vs CPU
                //    gui.getGame().input('o', cords[0], cords[1]); // CPU move handling
                //    turn = false;
                //}
            }

            // Redraw the updated grid and display the move
            window.clear(Color::Black);
            gui.DrawGrid(window);
            gui.MenuText(window, turn);
            gui.DrawScore(window);
            window.display();
        }

        string resultMessage = gui.game_end();
        if (!resultMessage.empty()) {
            gui.showMessageBox(window, resultMessage);
            turn = rand() % 2; // Reset turn for a new game
        }

        window.display();
    }
}
