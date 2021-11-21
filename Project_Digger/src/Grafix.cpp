#include "Grafix.h"
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
Grafix::Grafix()
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	std::vector<sf::Texture> textures(NUMTEXTURE);
	for (size_t i = 0; i < NUMTEXTURE; i++)//קריאת התמונות 
	{
		textures[i].loadFromFile(std::to_string(i + 1) + ".png");
		m_texturesVec.push_back(textures[i]);
	}
	
	m_sounds.openFromFile(std::to_string(1) + ".wav");
}

 Grafix& Grafix::getInstance()// single ton פונקציה זו אחראית על מימוש של 
{
	 static Grafix instance;
	 return instance;
}

const sf::Texture& Grafix::getTexture(char c)const
{
	// textureבודק איזה אובייקט נבחר ולפי זה מחזיר את ה

	switch (c)
	{
	case 'B': return m_texturesVec[0];
	case DIGGER:return m_texturesVec[1];
	case SPECIALMONSTER:return m_texturesVec[2];
	case REGULARMONSTER:return m_texturesVec[10];
	case STONE:return m_texturesVec[3];
	case DIYAMOND:return m_texturesVec[4];
	case WALL:return m_texturesVec[5];
	case GIFT:return m_texturesVec[6];
	case BACKGRAUND:return m_texturesVec[7];
	case NEWPLAY:return m_texturesVec[8];
	case EXIT:return m_texturesVec[9];
	case 'G':return m_texturesVec[11];
	case 'W':return m_texturesVec[12];
	default:return m_texturesVec[0];
		break;
	}

}




Grafix::~Grafix()
{
}