#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Player.h"
#include "Ball.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
	bool endGame;

	Player player;

	std::vector<Ball> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;
	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;
	
	void initVariables();
	void initWindow();
	void initFont();
	void initText();
public:
	//Constructor and Destructor
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void spawnBalls();
	int randomizeBallType() const;

	void updatePlayer();
	void updateCollision();
	void updateGUI();
	void update();

	void renderGUI(sf::RenderTarget& target);
	void render();
};

