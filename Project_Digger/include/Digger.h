#pragma once
#include "DynamicObject.h"
#include "Timer.h"
#include "Const.h"
class Level;
class Digger : public DynamicObject
{
public:
	Digger(const sf::Texture& texture, sf::Vector2f location, const sf::Vector2i sizeOfTexture,Timer& );
	void move(Level& l);
	void setDiggerDirection(int direction) { m_direction = direction; }//  לכיוון שיתקבל m_direction עידכון השדה  
	int getNumScores()const { return m_numScores; }
	int getLives()const { return m_lives; }
	int getNumStones() { return m_numStones; }//החזרת מספר האבנים
	void setNumScores(int a) { m_numScores += a; };//הוספת ניקוד 
	void decreasLives() { m_lives--; }// הורדת חיים של שחקן  
	void increasLives() { m_lives++; }
	void decreasnumOfStones() { m_numStones--; }// הורדה מכמות האבנים המותרת
	bool getNeedToSetBoard() { return m_needToSetBoard; }//החזרת אמת או שקר אם צריך להתחיל את השלב שוב
	void setNeedToSetBoard(bool flag) { m_needToSetBoard = flag; }//פונקציה שמעדכנת אם צריך להתחיל את השלב מחדש
	std::string  getClassName() { return typeid(Digger).name(); }
	void setNumStones(int a) { m_numStones = a; }
	void setNumLive(int a) { m_lives = a; }//עידכון מספר החיים
	bool getCanMove() { return m_canMove; }//אם השחקן יכול לזוז
	void setCanMove(bool flag) { m_canMove =flag; }
	void setNumStonesGift() { m_numStones += 2; }
	void setAddingTime() { m_time.addingMoreTimer(); }
	int getNumDiamond() { return m_numDiamond; }
	void setNumDiamond(int a) { m_numDiamond = a; }
	void decreaseDiamond() { m_numDiamond--; }
	~Digger();
	

private:
	int m_numScores;
	int m_lives;
	int m_numStones;
	bool m_needToSetBoard;
	bool m_canMove;
	int m_numDiamond;
	Timer& m_time;
};