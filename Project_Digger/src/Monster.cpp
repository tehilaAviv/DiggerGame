#include "Monster.h"
#include "Level.h"
Monster::Monster(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture) :
	DynamicObject(texture, location, sizeOfTexture), m_canMove(true)
{
	m_speed =55;
}
//--------------------------------------------------------------------------------------
void Monster::setDirection()//����� ������ ������ �����
{
	if (m_direction == 72)// �����
		m_direction--;
	else if (m_direction == 71)//�����
		m_direction++;
	else if (m_direction == 73)//�����
		m_direction++;
	else if (m_direction == 74)//����
		m_direction--;
}
//------------------------------------------------------------------------------------
Monster::~Monster()
{

}
