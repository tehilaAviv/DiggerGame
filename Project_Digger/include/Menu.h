#pragma once
#include <vector>
#include "Button.h"
#include "Const.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Level.h"
#include "StaticObject.h"
class Grafix;
class Menu
{
public:
	Menu( Grafix& grafix,sf::RenderWindow& window);
	void handlMenu(sf::RenderWindow& window, Grafix& grafix);
	void handlEvent(Grafix& grafix);
	void drawMenu() const;
	~Menu();

private:
	std::vector<Button>m_buttonOfMenu;
	StaticObject m_background;
	sf::RenderWindow& m_window;
};

