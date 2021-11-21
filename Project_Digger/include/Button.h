#pragma once
#include "Object.h"
class Button:public Object
{
public:
	Button(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture) :Object(texture, location, sizeOfTexture) {};
	bool contain(sf::Vector2f );
	std::string  getClassName() { return typeid(Button).name(); }
private:

};