#include "Button.h"

bool Button::contain(sf::Vector2f point)//����� �� ���� �� ������
{

	return m_display.getGlobalBounds().contains(point);
}
