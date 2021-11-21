#include "Button.h"

bool Button::contain(sf::Vector2f point)//בדיקה אם נלחץ על הכפתור
{

	return m_display.getGlobalBounds().contains(point);
}
