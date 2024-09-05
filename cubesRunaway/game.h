#pragma once
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/system.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
//a class that is technically a game engine

class Game
{
private:
	//private member variables that we dont want the user to modify
	sf::RenderWindow * window;
	sf::VideoMode VideoMode;
	sf::Event eve;
	void initVar();
	void initWin();
	void initEnemy();




	//enemy variables
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseRepeat;
	int healthBar;
	bool endGame;
	char answer;
	int rr;
	int rg;
	int rb;


	sf::Font font;



	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

public:

	//constructors and destructors
	Game();
	virtual ~Game();
	//game objects

	void updateMousePos();
	//the state of the window
	const bool running() const;
	void spawnEnemy();
	//pollevent bruh
	void pollEvent();


	//rendering
	void update();


	void updateEnemy();
	
	void renderEnemy();
	
	void render();

};

