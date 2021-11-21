#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class Stone :public StaticObject
{
public:
	Stone(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture)
		:StaticObject(texture, location, name, sizeOfTexture) {};
	std::string  getClassName() { return typeid(Stone).name(); }
	//void colide(Digger& digger);
	~Stone();

private:

};