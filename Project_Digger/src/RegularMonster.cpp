#include "RegularMonster.h"
RegularMonster::RegularMonster(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture):Monster(texture, location, sizeOfTexture)
{
}

void RegularMonster::move( Level& l)
{
	sf::Vector2f nextPos = DynamicObject::getNextPossotion(m_direction, l.getDeltatime() * m_speed);//nextPos ����� ������ ��� ������ ������� ������   
	if (l.isValid(nextPos)) //�� ������ ��� ����� ���� ����������
	
		l.handlMonsterCollision(nextPos, &*this);
	else//�� ������ ��� ���� ���� ���� ����� �����
		Monster::setDirection();
}




//------------------------------------------------------------------------------------
RegularMonster::~RegularMonster()
{
}
