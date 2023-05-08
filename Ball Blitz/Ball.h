#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Ball
{
private:
	sf::CircleShape shape;

	void initShape();
public:
	Ball();
	~Ball();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

