#pragma once
#include "Monster.h"
#include "Level.h"
#include "Digger.h"
class SpecialMonster: public Monster
{
public:
	SpecialMonster(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture);
	void move( Level& l);
	std::string  getClassName() { return typeid(SpecialMonster).name(); }
	~SpecialMonster();

private:
	
};