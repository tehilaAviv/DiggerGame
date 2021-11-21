#pragma once
#include <vector>
#include "Grafix.h"
#include "Board.h"
#include "Digger.h"
#include <SFML/Graphics.hpp>
#include "SpecialMonster.h"
#include "RegularMonster.h"
#include "Monster.h"
#include <string>
#include "Const.h"
#include <cstdlib>   
#include <thread>
#include <fstream>
#include "StaticObject.h"
#include "Timer.h"
#include "Collision.h"
#include "InformationDisplay.h"
#include <SFML/Audio.hpp>
class Level 
{
public:
	Level() = default;
	Level (Grafix& grafix,  sf::RenderWindow& window,int numLevel, int prevScore, int prevLive);
	int getTotalLive();
	void editDynamicObject(char currentChar, Grafix& grafix, sf::Vector2f Point);
	int getTotalScore();
	void run();
	void moveMosters();
	void print() ;
	bool checkArrow(int direction)const;
	void handlEvent();
	vector<StaticObject*> getNameIfIntersect(sf::FloatRect rect);
	void handlMonsterCollision(sf::Vector2f nextPos, DynamicObject* currentObject);
	void handlCollision(sf::Vector2f, Object*);
	bool isValid(sf::Vector2f v)const;
	float getDeltatime() { return m_timer.getDeltaTime(); }
	void decreaseLifeFroDigger() { m_digger->decreasLives(); }
	 DynamicObject* getDynamicObject(sf::FloatRect rect);
	 void deleteDynamicObject();
	 sf::Vector2f getDiggerPos() { return m_digger->getLocation(); }
	 void setCurrentMonster(DynamicObject* m) { m_currentMonster = m; }//עדכון המפלצת שאיתה נעבוד  
	 void setDiggetMove(bool flag) { m_isDiggerMove = flag; }
	 HitFunctionPtr lookup(const std::string& a, const std::string& b) { return m_collision.lookup(a,b); }
	 void setDiggerStone(int numStones) { m_digger->setNumStones(numStones); }
	 bool isClosed() { return m_isClosedByUser; }
	 bool getGameOver() { return m_gameOver; }
	 void setTimer(float a) { m_timer.setTime(a); }
	 
	 ~Level ();

private:

	DynamicObject* m_currentMonster;
	Timer m_timer;
	std::vector<DynamicObject*> m_dynamicObject;//וקטור של מפלצות
	Board m_board;
	bool m_isDiggerMove;
	Digger* m_digger;
	Grafix& m_grafix;
	sf::RenderWindow& m_window;
	StaticObject m_background;
	Collision m_collision;
	int m_numLevel;
	 InformationDisplay m_informationDisplay;
	 
	 bool m_isClosedByUser;
	 bool m_gameOver;
};

