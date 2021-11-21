#include "DynamicObject.h"
#include "collision.h"
#include "Level.h"
DynamicObject::DynamicObject(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture):Object(texture, location, sizeOfTexture), m_speed(100.f)
, m_direction(sf::Keyboard::Right)
{

}
void DynamicObject::directMoving(Level& l) 
{
	switch (m_direction)
	{
	case sf::Keyboard::Right: m_display.move(l.getDeltatime() * m_speed, 0);// ימניה
		break;
	case  sf::Keyboard::Left:  m_display.move(-l.getDeltatime() * m_speed, 0);// שמאלה
		break;
	case  sf::Keyboard::Down: m_display.move(0, l.getDeltatime() * m_speed);// למעלה 
		break;
	case  sf::Keyboard::Up:  m_display.move(0, -l.getDeltatime() * m_speed);// למטה
		break;
	default:
		break;
	}
	
}
//--------------------------------------------------------------------
sf::Vector2f DynamicObject::getNextPossotion(int direction,float offset)//הזזה לפי הכוון שנלחץ
{
	sf::Vector2f nextPos;
	switch (direction)
	{
	case sf::Keyboard::Right:
		return sf::Vector2f(Object::getLocation().x + offset, Object::getLocation().y);
	case sf::Keyboard::Left:
		return sf::Vector2f(Object::getLocation().x - offset, Object::getLocation().y);
	case sf::Keyboard::Up:
		return sf::Vector2f(Object::getLocation().x, Object::getLocation().y - offset);
	case sf::Keyboard::Down:
		return sf::Vector2f(Object::getLocation().x, Object::getLocation().y + offset);
	default:return sf::Vector2f(0, 0);
	}
	
		
	return nextPos;
}
//--------------------------------------------------------------------
void DynamicObject::changeLocation(sf::Vector2f vertex)//פונקיה זו מקבלת מיקום ומשנה אותו
{
	m_position = vertex;
	m_display.setPosition(vertex);
}

void DynamicObject::draw(sf::RenderWindow& window)const
{
	Object::draw(window);
}


void DynamicObject::handleColidtion(Level& l,Object& a)
{
	HitFunctionPtr phf = l.lookup(typeid(*this).name(), typeid(a).name());
	if (phf)
	{
		phf(*this, a);
	}
}

DynamicObject::~DynamicObject()
{

}

