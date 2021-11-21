#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>
class Wall :public StaticObject
{
public:
	Wall(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture)
		:StaticObject(texture, location, name, sizeOfTexture) {};
	std::string  getClassName() { return typeid(Wall).name(); }
	//void colide(Digger& digger);
	~Wall();
private:

};