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
	sleep(milliseconds(180));
}

void Game_Gui::showMessageBox(RenderWindow& window, string& resultMessage) {
	std::wstring message = std::wstring(resultMessage.begin(), resultMessage.end()) + L"\nDo you want to play again?";
	int response = MessageBox(nullptr, message.c_str(), L"Game Over", MB_YESNO | MB_ICONQUESTION);

	if (response == IDYES) {
		game.resetGame();
	}
	else if (response == IDNO) {
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

string Game_Gui::game_end() {
	if (game.getNo_X() >= 3 && game.check_Winner('x')) {
		game.updateScore('x');
		return game.getP1Name() + " wins!";
	}
	else if (game.getNo_O() >= 3 && game.check_Winner('o')) {
		game.updateScore('o');
		return game.getP2Name() + " wins!";
	}
	else if (game.getNo_X() + game.getNo_O() == 9) { 
		return "It's a draw!";
	}
	return "";
}


void Game_Gui::DrawStartMenu(RenderWindow& window) {
	Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Could not load font\n";
		return;
	}

	Text titleText;
	titleText.setFont(font);
	titleText.setString("Tic Tac Toe");
	titleText.setCharacterSize(50);
	titleText.setFillColor(Color::White);
	titleText.setPosition(250, 100);

	Text pvpOption;
	pvpOption.setFont(font);
	pvpOption.setString("1. Player vs Player");
	pvpOption.setCharacterSize(30);
	pvpOption.setFillColor(Color::White);
	pvpOption.setPosition(250, 250);

	Text pvcOption;
	pvcOption.setFont(font);
	pvcOption.setString("2. Player vs CPU");
	pvcOption.setCharacterSize(30);
	pvcOption.setFillColor(Color::White);
	pvcOption.setPosition(250, 300);

	window.draw(titleText);
	window.draw(pvpOption);
	window.draw(pvcOption);
}

int Game_Gui::HandleStartMenuInput(RenderWindow& window) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Num1) {
				return 1; // Player vs Player
			}
			if (event.key.code == Keyboard::Num2) {
				return 2; // Player vs CPU
			}
		}
	}
	return 0; 
}

vector<string> Game_Gui::GetPlayerNames(RenderWindow& window) {
	Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Could not load font\n";
		return {};
	}

	vector<string> playerNames = { "", "" };
	string currentInput = "";
	int currentPlayer = 0;

	Text promptText;
	promptText.setFont(font);
	promptText.setCharacterSize(30);
	promptText.setFillColor(Color::White);

	Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(30);
	inputText.setFillColor(Color::Cyan);

	while (currentPlayer < 2 && window.isOpen()) {
		window.clear(Color::Black);

		promptText.setString("Enter name for Player " + to_string(currentPlayer + 1) + ":");
		promptText.setPosition(200, 200);
		inputText.setString(currentInput);
		inputText.setPosition(200, 300);

		window.draw(promptText);
		window.draw(inputText);
		window.display();

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered) {
				if (event.text.unicode < 128 && event.text.unicode != '\b') {
					currentInput += static_cast<char>(event.text.unicode);
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::BackSpace && !currentInput.empty()) {
					currentInput.pop_back();
				}
				if (event.key.code == Keyboard::Enter && !currentInput.empty()) {
					playerNames[currentPlayer] = currentInput;
					currentInput = "";
					currentPlayer++;
				}
			}
		}
	}

	return playerNames;
}

int Game_Gui::DisplayStartMenu(RenderWindow& window) {
	Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Could not load font\n";
		return -1;
	}

	Text title("Tic Tac Toe", font, 50);
	title.setFillColor(Color::White);
	title.setStyle(Text::Bold | Text::Underlined);
	title.setPosition(200, 150);

	RectangleShape pvpButton(Vector2f(300, 50));
	pvpButton.setFillColor(Color(100, 100, 200));
	pvpButton.setPosition(200, 300);

	Text pvpText("Player vs Player", font, 25);
	pvpText.setFillColor(Color::White);
	pvpText.setPosition(240, 310);

	RectangleShape cpuButton(Vector2f(300, 50));
	cpuButton.setFillColor(Color(200, 100, 100));
	cpuButton.setPosition(200, 400);

	Text cpuText("Player vs CPU", font, 25);
	cpuText.setFillColor(Color::White);
	cpuText.setPosition(260, 410);

	while (window.isOpen()) {
		window.clear(Color::Black);

		window.draw(title);
		window.draw(pvpButton);
		window.draw(pvpText);
		window.draw(cpuButton);
		window.draw(cpuText);

		window.display();

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);

				if (pvpButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					return 1; // Player vs Player
				}
				if (cpuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					return 2; // Player vs CPU
				}
			}
		}
	}
	return -1; // Window closed
}

pair<string, string> Game_Gui::InputPlayerNames(RenderWindow& window, bool isPvP) {
	Font font;
	if (!font.loadFromFile("font.ttf")) {
		cout << "Could not load font\n";
		return { "Player 1", isPvP ? "Player 2" : "CPU" };
	}

	Text title("Enter Player Names", font, 40);
	title.setFillColor(Color::White);
	title.setPosition(180, 100);

	string p1Name = "", p2Name = isPvP ? "" : "CPU"; 
	Text inputText1("Player 1: ", font, 30);
	inputText1.setFillColor(Color::White);
	inputText1.setPosition(100, 250);

	Text inputText2("Player 2: ", font, 30);
	inputText2.setFillColor(Color::White);
	inputText2.setPosition(100, 350);

	RectangleShape textBox1(Vector2f(400, 50));
	textBox1.setFillColor(Color(50, 50, 50));
	textBox1.setPosition(250, 250);

	RectangleShape textBox2(Vector2f(400, 50));
	textBox2.setFillColor(Color(50, 50, 50));
	textBox2.setPosition(250, 350);

	bool isEditingP1 = true; 

	while (window.isOpen()) {
		window.clear(Color::Black);

		// Draw elements
		window.draw(title);
		window.draw(inputText1);
		window.draw(inputText2);
		window.draw(textBox1);
		window.draw(textBox2);

		Text p1NameText(p1Name, font, 25);
		p1NameText.setFillColor(isEditingP1 ? Color::Cyan : Color::White);
		p1NameText.setPosition(260, 260);

		Text p2NameText(p2Name, font, 25);
		p2NameText.setFillColor(!isEditingP1 ? Color::Cyan : Color::White);
		p2NameText.setPosition(260, 360);

		window.draw(p1NameText);
		window.draw(p2NameText);

		window.display();

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::TextEntered) {
				char inputChar = static_cast<char>(event.text.unicode);

				if (inputChar == '\b') { 
					if (isEditingP1 && !p1Name.empty()) {
						p1Name.pop_back();
					}
					else if (!isEditingP1 && !p2Name.empty() && isPvP) {
						p2Name.pop_back();
					}
				}
				else if (inputChar == '\r') {
					if (isEditingP1) {
						isEditingP1 = false; // Move to Player 2
					}
					else {
						if (isPvP && !p1Name.empty() && !p2Name.empty()) {
							return { p1Name, p2Name };
						}
						else if (!isPvP && !p1Name.empty()) {
							return { p1Name, "CPU" };
						}
					}
				}
				else if (inputChar >= 32 && inputChar <= 126) { 
					if (isEditingP1 && p1Name.size() < 15) {
						p1Name += inputChar;
					}
					else if (!isEditingP1 && isPvP && p2Name.size() < 15) {
						p2Name += inputChar;
					}
				}
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				if (textBox1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					isEditingP1 = true;
				}
				else if (textBox2.getGlobalBounds().contains(mousePos.x, mousePos.y) && isPvP) {
					isEditingP1 = false;
				}
			}
		}
	}

	return { "Player 1", isPvP ? "Player 2" : "CPU" };
}
