#include "Game_Gui.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
using namespace sf;

int main() {
	RenderWindow window(VideoMode(700, 800), "Tic-Tac-Toe");
	Game_Gui gui;
	bool turn = rand() % 2;
	bool gameEnd = false;

	while (window.isOpen()) {
		window.clear(Color::Black);
		vector<int> cords = gui.HandleInput(window);

		if (cords[0] != -1 && cords[1] != -1) {
			// prints info on console
			turn == false ? std::cout << "X" : std::cout << "O";
			cout << " placed at: (" << cords[0] << ", " << cords[1] << ")\n";

			// Handle the move
			if (turn == false) {
				gui.getGame().input('x', cords[0], cords[1]);
				turn = true;
			}
			else {
				gui.getGame().input('o', cords[0], cords[1]);
				turn = false;
			}
		}
		gameEnd = gui.game_end();
		gui.MenuText(window, turn);
		gui.DrawScore(window);
		gui.DrawGrid(window);
		window.display();

		if (gameEnd) {
			gui.showMessageBox(window);
		}
		gameEnd = false;
	}

	return 0;
}