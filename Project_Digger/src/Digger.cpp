#include "Digger.h"
#include "Level.h"
Digger::Digger(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture, Timer& time):DynamicObject(texture, location, sizeOfTexture),m_lives(MAXLIVE)
, m_needToSetBoard(false), m_numScores(0),m_canMove(true),m_time(time)
{
}

void Digger::move( Level& l)
{
	
		sf::Vector2f nextPos = DynamicObject::getNextPossotion(m_direction, m_speed * l.getDeltatime());
		if (l.isValid(nextPos))//אם הצעד הבא של השחקן בגבולות
			l.handlCollision(nextPos, &*this);
		else
			l.setDiggetMove(false);//השחקן לא יכול לזוז
	
	

}

Digger::~Digger()
{
}

