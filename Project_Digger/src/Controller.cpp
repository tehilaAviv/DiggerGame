#include "Controller.h"
#include "Level.h"
#include "Menu.h"
Controller::Controller()
{
}

void Controller::runGame()
{
	
	Grafix& grafix = Grafix::getInstance();
	sf::RenderWindow window(sf::VideoMode(800, 800), "play");
	Menu menu(grafix, window);
	menu.handlMenu(window, grafix);
}

