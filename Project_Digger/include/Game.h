#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Const.h"
class Grafix;
class Game
{
public:
	Game(sf::RenderWindow& w, Grafix& g);
	void manage(Grafix& g);
	void showWin();
	void show();
	~Game();

private:
	sf::RenderWindow& m_window;
	StaticObject m_backgroundGameOver;
	StaticObject m_backgroundWin;
};

