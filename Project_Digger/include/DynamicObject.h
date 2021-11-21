#pragma once
#include "Object.h"



class Level;
class DynamicObject : public Object
{
public:
	DynamicObject(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture);
	void directMoving(Level& l);
	virtual void move(Level&) = 0;
	sf::Vector2f getNextPossotion(int direction, float offset);
	void changeLocation(sf::Vector2f v);
	 void draw(sf::RenderWindow& window) const;
	void handleColidtion(Level& ,Object& a);
	~DynamicObject();
	
protected:
	float m_speed;
	int m_direction;//כיוון
};
