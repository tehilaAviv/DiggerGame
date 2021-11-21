#pragma once
#include "StaticObject.h"
#include <vector>
#include "Grafix.h"
#include <fstream>
#include "Gift.h"
#include "Stone.h"
#include "Diamond.h"
#include "Wall.h"

class Level;

using std::vector;

class Board
{
public:
	Board();
	void editBoard(Grafix& grafix, Level& game,int numLevel);
	void clear();

	void drowBoard(sf::RenderWindow&);
	char checkTypeObject(char c)const;
	sf::Vector2i  getSizeOfShape()const;
	vector<StaticObject*> getNameIfIntersect(sf::FloatRect rect);
	int getNumDiamond();
	~Board();
private:
	vector <vector<StaticObject*>> m_editBoard;
	sf::Vector2i m_sizeOfShape;//מחזיק את גודל הצורה

};

