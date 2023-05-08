#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.0f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/BrunoAceSC-Regular.ttf"))
		std::cout << "Error loading font"<<"\n";
}

void Game::initText()
{
	//GUI text
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);

	//End game Text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::White);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(
		sf::Vector2f(
			200,100
		)
	);
	this->endGameText.setString("Game Over");
}

//Constructor and Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

//Functions
const bool Game::running() const
{
	return this->window->isOpen(); // && !endGame;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnBalls()
{
	//Balls Spawner

	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.0f;
	else
	{
		if (this->balls.size() < maxBalls)
		{
			this->balls.push_back(Ball(*this->window, this->randomizeBallType()));
			this->spawnTimer = 0.0f;
		}
	}
}

int Game::randomizeBallType() const
{
	int type = BallTypes::DEFAULT;
	int n = rand() % 100 + 1;

	if (n > 60 && n <= 90)
	{
		type = BallTypes::DAMAGING;
	}
	else if (n > 90)
	{
		type = BallTypes::HEALING;
	}

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallTypes::DEFAULT:
				this->points++;
				break;
			case BallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case BallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			//destroy ball
			this->balls.erase(this->balls.begin() + i);
		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Score: " << this->points << "\n"
		<<"Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";
	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (!this->endGame)
	{
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGUI();
	}
}

void Game::renderGUI(sf::RenderTarget& target)
{
	target.draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	//Render stuff
	this->player.render(this->window);

	for (auto i : balls)
	{
		i.render(*this->window);
	}

	//Render GUI
	this->renderGUI(*this->window);

	if (this->endGame)
		this->window->draw(endGameText);

	this->window->display();
}