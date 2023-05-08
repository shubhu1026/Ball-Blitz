#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 10.0f;
}

void Player::initShape()
{
	//sets player shape properties
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.0f, 50.0f));
}

Player::Player(float x, float y)
{
	//sets player position and init variables
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

void Player::updateInput()
{
	//move with keyboard input

	//Left input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.0f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.0f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	if (playerBounds.left <= 0.0f)
		this->shape.setPosition(0.0f, playerBounds.top);
	//Right
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);

	//Top
	if (playerBounds.top <= 0.0f)
		this->shape.setPosition(playerBounds.left, 0.0f);
	//Bottom
	else if (playerBounds.top + playerBounds.height >= target->getSize().y)
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);


	//Corners

	//Top left Corner
	if (playerBounds.left <= 0.0f && playerBounds.top <= 0.0f)
		this->shape.setPosition(0.0f, 0.0f);
	//Top Right Corner
	else if (playerBounds.top <= 0.0f && (playerBounds.left + playerBounds.width >= target->getSize().x))
		this->shape.setPosition(target->getSize().x - playerBounds.width, 0.0f);
	//Bottom Left Corner
	else if ((playerBounds.top + playerBounds.height >= target->getSize().y) && (playerBounds.left <= 0.0f))
		this->shape.setPosition(0.0f, target->getSize().y - playerBounds.height);
	//Bottom Right Corner
	else if ((playerBounds.top + playerBounds.height >= target->getSize().y) && (playerBounds.left + playerBounds.width >= target->getSize().x))
		this->shape.setPosition(target->getSize().x - playerBounds.width, target->getSize().y - playerBounds.height);
}

void Player::update(const sf::RenderTarget* target)
{
	/*
		moves player
	*/
	this->updateInput();

	//window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	//renders the player shape

	target->draw(this->shape);
}
