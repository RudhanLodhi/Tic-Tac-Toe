#include "Game_Gui.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace sf;
using namespace std;

Game_Gui::Game_Gui() {
	srand(time(0));
}

void Game_Gui::DrawGrid(RenderWindow& window) {
	RectangleShape line(Vector2f(600, 5));

	// Horizontal lines
	line.setPosition(50, 350);
	window.draw(line);
	line.setPosition(50, 550);
	window.draw(line);

	// Vertical lines
	line.setSize(Vector2f(5, 600));
	line.setPosition(250, 150);
	window.draw(line);
	line.setPosition(450, 150);
	window.draw(line);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game.getMap(i, j) == 'x') {
				DrawCross(window, j, i);
			}
			if (game.getMap(i, j) == 'o') {
				DrawCircle(window, j, i);
			}
		}
	}
}

void Game_Gui::DrawCross(RenderWindow& window, float col, float row) {
	RectangleShape line(Vector2f(200, 5));
	line.setFillColor(Color::Red);

	float x = (80 + col * 200);
	float y = (180 + row * 200);

	line.setPosition(x, y);
	line.setRotation(45);
	window.draw(line);

	line.setRotation(-45);
	line.setPosition(x, y + 138);
	window.draw(line);
}

void Game_Gui::DrawCircle(RenderWindow& window, float col, float row) {
	CircleShape circle(70);

	circle.setOutlineThickness(5);
	circle.setOutlineColor(Color::Green);
	circle.setFillColor(Color::Transparent);

	float x = 80 + col * 200;
	float y = 180 + row * 200;

	circle.setPosition(x, y);
	window.draw(circle);
}

void Game_Gui::Clicksound() {
	SoundBuffer buffer;
	buffer.loadFromFile("click sound.wav");
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	sleep(milliseconds(150));
}

void Game_Gui::showMessageBox(RenderWindow& window) {
	int response = MessageBox(nullptr, L"Do you want to play again?", L"Game Over", MB_YESNO | MB_ICONQUESTION);

	if (response == IDYES) {
		cout << "User chose to play again.\n";
		game.resetGame();
	}
	else if (response == IDNO) {
		cout << "User chose to exit the game.\n";
		window.close();
	}
}

vector<int> Game_Gui::HandleInput(RenderWindow& window) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}

		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (worldPos.x >= 50 && worldPos.x <= 650 && worldPos.y >= 150 && worldPos.y <= 750) {
					int row = (worldPos.y - 150) / 200;
					int col = (worldPos.x - 50) / 200;

					if (row >= 0 && row < 3 && col >= 0 && col < 3) {
						Clicksound();
						return { row, col };
					}
				}
			}
		}
	}
	return { -1, -1 };
}

void Game_Gui::MenuText(RenderWindow& window, bool turn) {
	Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Could not load font\n";
		return;
	}

	Text player1Text;
	player1Text.setFont(font);
	player1Text.setString(game.getP1Name());
	player1Text.setCharacterSize(28);
	player1Text.setPosition(100, 50);

	Text player2Text;
	player2Text.setFont(font);
	player2Text.setString(game.getP2Name());
	player2Text.setCharacterSize(28);
	player2Text.setPosition(500, 50);

	Text turnText;
	turnText.setFont(font);
	turnText.setString("Your turn");
	turnText.setCharacterSize(20);

	if (!turn) {
		player1Text.setFillColor(Color::Green);
		turnText.setPosition(100, 90);
		window.draw(player1Text);
		window.draw(turnText);
		window.draw(player2Text);
	}
	else {
		player2Text.setFillColor(Color::Green);
		turnText.setPosition(500, 90);
		window.draw(player1Text);
		window.draw(player2Text);
		window.draw(turnText);
	}
}

void Game_Gui::DrawScore(RenderWindow& window) {
	Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Could not load font\n";
		return;
	}

	int p1Score = game.getScore('x');
	int p2Score = game.getScore('o');

	Color p1Color = Color::White;
	Color p2Color = Color::White;

	if (p1Score > p2Score) {
		p1Color = Color::Green;
		p2Color = Color::Red;
	}
	else if (p1Score < p2Score) {
		p1Color = Color::Red;
		p2Color = Color::Green;
	}

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score");
	scoreText.setCharacterSize(36);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(350 - scoreText.getLocalBounds().width / 2, 20);

	RectangleShape line(Vector2f(5, 50));
	line.setFillColor(Color::White);
	line.setPosition(350, 70);

	Text p1ScoreText;
	p1ScoreText.setFont(font);
	p1ScoreText.setString(to_string(p1Score));
	p1ScoreText.setCharacterSize(30);
	p1ScoreText.setFillColor(p1Color);
	p1ScoreText.setPosition(280, 80);

	Text p2ScoreText;
	p2ScoreText.setFont(font);
	p2ScoreText.setString(to_string(p2Score));
	p2ScoreText.setCharacterSize(30);
	p2ScoreText.setFillColor(p2Color);
	p2ScoreText.setPosition(420 - p2ScoreText.getLocalBounds().width, 80);

	window.draw(scoreText);
	window.draw(line);
	window.draw(p1ScoreText);
	window.draw(p2ScoreText);
}

bool Game_Gui::game_end()
{
	if (game.getNo_X() >= 3 && game.check_Winner('x')) {
		cout << "player 1 wins" << endl;
		game.updateScore('x');
		return true;
	}
	else if (game.getNo_O() >= 3 && game.check_Winner('o')) {
		cout << "player 2 wins" << endl;
		game.updateScore('o');
		return true;
	}
	else if (game.getNo_X() == 5 || game.getNo_O() == 5) {
		cout << "draw" << endl;
		return true;
	}
	return false;
}