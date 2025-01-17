#include "Game_Gui.h"
#include "Solver.h"
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;

void Redraw_Window(RenderWindow& window, Game_Gui& gui, bool turn) {
    window.clear(Color::Black);
    gui.DrawGrid(window);
    gui.MenuText(window, turn);
    gui.DrawScore(window);
    window.display();
}

int main() {
    RenderWindow window(VideoMode(700, 800), "Tic-Tac-Toe");
    Game_Gui gui;
    int mode = gui.DisplayStartMenu(window);
    if (mode == -1) {
        return 0;
    }

    if (mode == 1) { // PVP
        pair<string, string> playerNames = gui.InputPlayerNames(window, true);
        gui.getGame().setP1Name(playerNames.first);
        gui.getGame().setP2Name(playerNames.second);
    }
    else if (mode == 2) { // PVC
        pair<string, string> playerNames = gui.InputPlayerNames(window, false);
        gui.getGame().setP1Name(playerNames.first);
        gui.getGame().setP2Name("CPU");
    }

    bool turn = rand() % 2;

    // Main game loop
    while (window.isOpen()) {
        if (mode == 2 && turn) { // CPU move in PVC
            Solver cpu(gui.getGame());
            pair<int, int> move = cpu.findBestMove();
            gui.getGame().input('o', move.first, move.second); // CPU makes a move
            turn = false;

            Redraw_Window(window, gui, turn);

            // if game ends during cpu moves it needs to be evaluated here
            string resultMessage = gui.game_end();
            if (!resultMessage.empty()) {
                gui.showMessageBox(window, resultMessage);
                gui.getGame().resetGame(); 
                turn = rand() % 2;        
                continue;                  
            }
        }
        else { // Player move
            vector<int> cords = gui.HandleInput(window);
            if (cords[0] != -1 && cords[1] != -1) {
                if (!turn) { // P1
                    if (gui.getGame().input('x', cords[0], cords[1])) {
                        turn = true;
                    }
                }
                else if (mode == 1) { // P2 in PVP
                    if (gui.getGame().input('o', cords[0], cords[1])) {
                        turn = false;
                    }
                }

                Redraw_Window(window, gui, turn);

                string resultMessage = gui.game_end();
                if (!resultMessage.empty()) {
                    gui.showMessageBox(window, resultMessage);
                    gui.getGame().resetGame(); 
                    turn = rand() % 2;
                    continue;
                }
            }
        }
        Redraw_Window(window, gui, turn);
    }
}
