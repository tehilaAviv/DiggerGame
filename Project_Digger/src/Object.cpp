#include "Object.h"

Object::Object(const sf::Texture& texture1, const sf::Vector2f location, const sf::Vector2i sizeOfTexture)
{
	m_display.setTexture(texture1);
	m_display.setPosition(location);
	m_position = location;
	m_display.scale((float)(sizeOfTexture.x) / texture1.getSize().x, (float)sizeOfTexture.y / texture1.getSize().y);// ���� �� ������ ����� �����
}
sf::FloatRect Object::getFloatRectWithOfsset(sf::Vector2f nextPos)//������� ������� �� ����� ����� ���� ���� �����
{
	sf::Sprite temp = m_display;//����� ��� ������ ����� �� ����� ������ ����� �����    
	temp.setPosition(nextPos);//����� �� ������ ������ ������ ��� 
	return temp.getGlobalBounds();//����� ����� ����� ����
}

sf::FloatRect Object::getFloatRect()//����� �� ����� ����� ������
{
	return m_display.getGlobalBounds();
}


void Object::draw(sf::RenderWindow& window) const 
{
	window.draw(m_display);
	
}

bool Object::intersection(sf::FloatRect rect)// ����� ��� �� ����� ����� ������ ���� �� ����� ����� ���  
{
	return m_display.getGlobalBounds().intersects(rect);
}

Object::~Object()
{
}
