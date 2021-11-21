#include "Object.h"

Object::Object(const sf::Texture& texture1, const sf::Vector2f location, const sf::Vector2i sizeOfTexture)
{
	m_display.setTexture(texture1);
	m_display.setPosition(location);
	m_position = location;
	m_display.scale((float)(sizeOfTexture.x) / texture1.getSize().x, (float)sizeOfTexture.y / texture1.getSize().y);// מסדר את התמונה לגודל הרצוי
}
sf::FloatRect Object::getFloatRectWithOfsset(sf::Vector2f nextPos)//פונקציה שמחזירה את המלבן החוסם לאחר הזזה כלשהי
{
	sf::Sprite temp = m_display;//משתנה עזר המהווה העתקה של המלבן הנוכחי ועליו נעבוד    
	temp.setPosition(nextPos);//מעדכן את המיקום הנוכחי למיקום הבא 
	return temp.getGlobalBounds();//החזרת המלבן החוסם החדש
}

sf::FloatRect Object::getFloatRect()//מחזיר את המלבן החוסם הנוכחי
{
	return m_display.getGlobalBounds();
}


void Object::draw(sf::RenderWindow& window) const 
{
	window.draw(m_display);
	
}

bool Object::intersection(sf::FloatRect rect)// מחזיר אמת אם המלבן החוסם הנוכחי נחתך עם המלבן החוסם הבא  
{
	return m_display.getGlobalBounds().intersects(rect);
}

Object::~Object()
{
}
