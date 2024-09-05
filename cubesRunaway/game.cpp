#include "game.h"
void Game::initVar()
{
	this->window = nullptr;
	//enemy stuff
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	this->points = 0;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 100;
	this->mouseRepeat = false;
	this->healthBar = 10;
	this->endGame = false;
	this->answer;
	this->rr = rand() % 255;
	this->rb = rand() % 255;
	this->rg = rand() % 255;

}
void Game::initWin()
{ //functions for controlling all window properties
	this->VideoMode.height = 500;
	this->VideoMode.width = 700;

	this->window = new sf::RenderWindow(this->VideoMode, "game 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}
void Game::initEnemy()
{	//functions to control all enemy properties 
	this->enemy.setPosition(this->window->getSize().x / 2 - 50,this->window->getSize().y / 2 - 50);
	this->enemy.setSize(sf::Vector2f(50.f,50.f));
	this->enemy.setFillColor(sf::Color(rr, rg, rb));
	this->enemy.setOutlineColor(sf::Color(rr, rg, rb));
	this->enemy.setOutlineThickness(2.f);


}
Game::Game()
{	//the game contuctor
	initVar();
	initWin();
	initEnemy();
	

}

Game::~Game()
{	//game destrcutor for memory leaks
	delete this->window;
}

void Game::updateMousePos()
{
	//doing things to when the mouse interacts with the window only by tracking its movement
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(this->mousePositionWindow);
}

const bool Game::running() const
{
	//function to tell us if the game is running or not
	return this->window->isOpen();
}

void Game::spawnEnemy()
{	//spawns an enemy in a random position on the window {with a random color and a random size} (to do)
	this->enemy.setPosition(
		static_cast<float>(rand()%static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f

	);
	this->enemy.setFillColor(sf::Color::Green);
	//push the enemy into the vector of enemies to track all enemies that exist within the program
	this->enemies.push_back(this->enemy);
}

void Game::pollEvent()
{	//replacing the while loop from the main.cpp file for easier usablity and for faster running 
	while (window->pollEvent(this->eve))
	{
		switch (this->eve.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyReleased:
			if (eve.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			break;
		}
	}
}








void Game::update()
{	//updates the window by adding a frame and a frame...
	this->pollEvent();
	
	if (endGame == false )
	{
		this->updateMousePos();
		this->updateEnemy();
	}
	else
	{
		std::cout << "do you want to play again(N:NO  ,  Y:YES)" << '\n';
		std::cin >> answer;
		switch (answer)
		{
		case 'Y':
			this->healthBar = 10;
			this->endGame = false;
			
			break;
		case 'N' :
			this->window->close();
			break;

		}
	}
}


void Game::updateEnemy()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.5f;
		}
		else
		{
			this->enemySpawnTimer += 1;
		}
		for (int i = 0; i < this->enemies.size(); i++)
		{
			bool deleted = false;
			this->enemies[i].move(0.f, 5.f);
			if (this->enemies[i].getPosition().y == this->window->getSize().y + 50.f)
			{
				this->enemies.erase(this->enemies.begin() + i);
				if (this->healthBar == 0) 
				{
					std::cout << "GAME OVER" << '\n' << "your score was : " << points << '\n';
					this->endGame = true; 
				}
				else
				{
					this->healthBar--;
					std::cout << "your health is : " << healthBar << '\n';
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->mouseRepeat == false)
			{
				
				this->mouseRepeat = true;
				bool deleted = false;
				
				//this prevents the player from spamming the mouse because when the player clicks the mouse the deleted is set to true thus the functions wont be working;
				for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
				{
					if (this->enemies[i].getGlobalBounds().contains(this->mousePositionView))
					{
						
							this->enemies.erase(this->enemies.begin() + i);
							
							this->points++;
							deleted = true;
					}
				}
			}
			
			

		}
		else
		{
			this->mouseRepeat = false;
		}
	}
}

void Game::renderEnemy()
{	//goes through every entity in the vector and draws it 
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	this->window->clear();
	this->renderEnemy();
	this->window->display();
}



