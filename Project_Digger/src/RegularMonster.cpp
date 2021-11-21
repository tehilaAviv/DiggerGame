#include "RegularMonster.h"
RegularMonster::RegularMonster(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture):Monster(texture, location, sizeOfTexture)
{
}

void RegularMonster::move( Level& l)
{
	sf::Vector2f nextPos = DynamicObject::getNextPossotion(m_direction, l.getDeltatime() * m_speed);//nextPos חישוב המיקום הבא שיתבצע והכנסתו למשתנה   
	if (l.isValid(nextPos)) //אם המיקום הבא בתחום נטפל בהתנגשויות
	
		l.handlMonsterCollision(nextPos, &*this);
	else//אם המיקום הבא חסום נשנה כוון לכוון הנגדי
		Monster::setDirection();
}




//------------------------------------------------------------------------------------
RegularMonster::~RegularMonster()
{
}
