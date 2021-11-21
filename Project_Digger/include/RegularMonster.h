#pragma once
#include <SFML/Audio.hpp>
#include "Monster.h"
#include "Level.h"
#include "Digger.h"

class RegularMonster:public Monster
{
public:
	RegularMonster(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture);
	void move( Level& l);
	
	std::string  getClassName() { return typeid(RegularMonster).name(); }
	
	~RegularMonster();

private:

};
