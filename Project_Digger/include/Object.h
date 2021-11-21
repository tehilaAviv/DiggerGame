#pragma once
#include <SFML/Graphics.hpp>
class Digger;

class Object
{
public:
	
	Object(const sf::Texture& texture1, const sf::Vector2f location, const sf::Vector2i sizeOfTexture);
	sf::FloatRect getFloatRectWithOfsset(sf::Vector2f nextPos);
	sf::FloatRect getFloatRect();
	Object() = default;
	virtual void draw(sf::RenderWindow& window)const;// פונקציה וירטואלית שאחראית על ציור האובייקטים
	bool intersection(sf::FloatRect rect);
	virtual std::string  getClassName() = 0;
	const sf::Texture* getTexture()const { return m_display.getTexture(); }
	sf::Vector2f getLocation()const{return m_display.getPosition();}
	sf::Vector2f getSizeOfSprite()const {return sf::Vector2f(m_display.getGlobalBounds().width, m_display.getGlobalBounds().height);}//החזרת הגובה והרוחב של המלבן החוסם
	~Object();

protected:
	sf::Vector2f m_position;
	sf::Sprite m_display;
};

