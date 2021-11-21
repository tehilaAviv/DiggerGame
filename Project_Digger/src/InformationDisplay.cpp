#include "InformationDisplay.h"

InformationDisplay::InformationDisplay(Grafix& g)
{
	m_Time.setFont(g.getFont());
	m_Time.setFillColor(sf::Color::Black);
	m_Time.setPosition(460, 30);

	m_level.setFont(g.getFont());
	m_level.setFillColor(sf::Color::Black);
	m_level.setPosition(610, 30);

	m_life.setFont(g.getFont());
	m_life.setFillColor(sf::Color::Black);
	m_life.setPosition(50,30 );

	m_score.setFont(g.getFont());
	m_score.setFillColor(sf::Color::Black);
	m_score.setPosition(160, 30);

	m_stone.setFont(g.getFont());
	m_stone.setFillColor(sf::Color::Black);
	m_stone.setPosition(310, 30);


}
void InformationDisplay::setStringStone(const std::string stone) { m_stone.setString(stone); }
void InformationDisplay::setStringScore(const std::string score) { m_score.setString(score); }
void InformationDisplay::setStringtime(const std::string time) { m_Time.setString(time); }
void InformationDisplay::setStringlife(const std::string life) { m_life.setString(life); }
void InformationDisplay::setStringlevel(const std::string level) { m_level.setString(level); }



void InformationDisplay::draw(sf::RenderWindow& window)
{
	window.draw(m_score);
	window.draw(m_stone);
	window.draw(m_Time);
	window.draw(m_life);
	window.draw(m_level);
}

InformationDisplay::~InformationDisplay()
{
}
