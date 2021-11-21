#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Digger.h"
class Diamond:public StaticObject
{
public:
	Diamond(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture)
		:StaticObject(texture, location, name, sizeOfTexture) {};
	std::string  getClassName() { return typeid(Diamond).name(); }
	//void colide(Digger& digger);
	~Diamond();

private:

};