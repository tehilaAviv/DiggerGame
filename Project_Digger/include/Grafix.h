#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Const.h"


class Grafix
{
public:
	static Grafix& getInstance();
	const sf::Texture& getTexture(char ch)const;
	sf::Font& getFont() { return m_font; }
	sf::Music m_sounds;
	~Grafix() ;
private:
	Grafix();
	sf::Font m_font;
	std::vector<sf::Texture> m_texturesVec;
};
 
