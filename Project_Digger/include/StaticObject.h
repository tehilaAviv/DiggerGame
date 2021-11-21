#pragma once
#include "Object.h"
class StaticObject : public Object
{
public:
	StaticObject(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture) ;
	char getName()const { return m_name; };//מחזיר איזה אובייקט סטטי יש 
	std::string  getClassName(){ return typeid(StaticObject).name(); }//מחזיר איזה אובייקט סטטי יש
	void clean(const sf::Texture& texture) { m_display.setTexture(texture); m_name = ' '; }//פונקציה שאחראית על מחיקת האובייקט מהלוח
	void clean(char a) {  m_name = a; }//פונקציה שמקבלת תו ומעדכנת את השדה לתו הזה 
	~StaticObject();

protected:
	char m_name;
};