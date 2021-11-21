#include "SpecialMonster.h"

SpecialMonster::SpecialMonster(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture ) :Monster(texture, location, sizeOfTexture)
{
}

void SpecialMonster::move( Level& l)//פונקציה זו אחראית על תזוזת המפלצות המיוחדות
{
	sf::Vector2f nextPos = DynamicObject::getNextPossotion(m_direction, l.getDeltatime() * m_speed);//  חישוב המיקום הבא ע"י כיוון ודרך
			auto locationMonster = m_display.getPosition();//משתנה המחזיק את מיקום המפלצת
			auto locationPlayer = l.getDiggerPos();//משתנה המחזיק את מיקום השחקן
			if (locationMonster.y <= locationPlayer.y && locationMonster.x <= locationPlayer.x)
			{
				//ימינה
				nextPos = { m_display.getPosition().x + l.getDeltatime() * m_speed, m_display.getPosition().y };
				
			}

			if (locationMonster.y <= locationPlayer.y && locationMonster.x >= locationPlayer.x)
			{    //למטה
				nextPos = { m_display.getPosition().x, m_display.getPosition().y + l.getDeltatime() * m_speed };
				
			}

			else if (locationMonster.y >= locationPlayer.y && locationMonster.x <= locationPlayer.x)
			{	//למעלה
				nextPos = { m_display.getPosition().x, m_display.getPosition().y - l.getDeltatime() * m_speed };
			
				
			}

			else if (locationMonster.y >= locationPlayer.y && locationMonster.x >= locationPlayer.x)
			{
				//שמאלה


				nextPos = { m_display.getPosition().x - l.getDeltatime() * m_speed, m_display.getPosition().y };
			}
			if (l.isValid(nextPos)) { // חישבנו את המיקום האופטימלי ולאחר מכן בדקנו אם הוא בתחום, אם כן ביצענו את שינוי המקום. אם לא  שינינו את הכיוון לכיוון הנגדי
				l.handlMonsterCollision(nextPos, &*this);
			}
			else
			{
			 setDirection();
				
			}
		}


//-----------------------------------------------------------------------------


SpecialMonster::~SpecialMonster()
{
}
