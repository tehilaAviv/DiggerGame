#pragma once
#include "Object.h"
class StaticObject : public Object
{
public:
	StaticObject(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture) ;
	char getName()const { return m_name; };//����� ���� ������� ���� �� 
	std::string  getClassName(){ return typeid(StaticObject).name(); }//����� ���� ������� ���� ��
	void clean(const sf::Texture& texture) { m_display.setTexture(texture); m_name = ' '; }//������� ������� �� ����� �������� �����
	void clean(char a) {  m_name = a; }//������� ������ �� ������� �� ���� ��� ��� 
	~StaticObject();

protected:
	char m_name;
};