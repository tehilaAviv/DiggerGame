#pragma once
#include <SFML/Graphics.hpp>
#include "Grafix.h"
//#include "Digger.h"
class InformationDisplay
{
public:
	InformationDisplay(Grafix&);
	void setStringStone(const std::string stone);
	void setStringScore(const std::string score);
	void setStringtime(const std::string time);
	void setStringlife(const std::string life);
	void setStringlevel(const std::string level);
	void draw(sf::RenderWindow& window);
	~InformationDisplay();

private:
	sf::Text m_life;
	sf::Text m_score;
	sf::Text m_stone;
	sf::Text m_level;
	sf::Text m_Time;
};
