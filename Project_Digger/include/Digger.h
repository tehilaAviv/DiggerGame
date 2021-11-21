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
	void setDiggerDirection(int direction) { m_direction = direction; }//  ������ ������ m_direction ������ ����  
	int getNumScores()const { return m_numScores; }
	int getLives()const { return m_lives; }
	int getNumStones() { return m_numStones; }//����� ���� ������
	void setNumScores(int a) { m_numScores += a; };//����� ����� 
	void decreasLives() { m_lives--; }// ����� ���� �� ����  
	void increasLives() { m_lives++; }
	void decreasnumOfStones() { m_numStones--; }// ����� ����� ������ ������
	bool getNeedToSetBoard() { return m_needToSetBoard; }//����� ��� �� ��� �� ���� ������ �� ���� ���
	void setNeedToSetBoard(bool flag) { m_needToSetBoard = flag; }//������� ������� �� ���� ������ �� ���� ����
	std::string  getClassName() { return typeid(Digger).name(); }
	void setNumStones(int a) { m_numStones = a; }
	void setNumLive(int a) { m_lives = a; }//������ ���� �����
	bool getCanMove() { return m_canMove; }//�� ����� ���� ����
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