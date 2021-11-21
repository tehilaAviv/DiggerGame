#pragma once
#include "StaticObject.h"
#include "Timer.h"
class Gift:public StaticObject
{
public:
	Gift(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture, int sk)
		:StaticObject(texture, location, name, sizeOfTexture), m_specialKey(sk) {};
	int getSpecialKey() { return m_specialKey; }//מחזיר איזה מתנה נבחרה
	std::string  getClassName() { return typeid(Gift).name(); }
	~Gift();
private:
	int m_specialKey;
	Timer m_time;
};

