#include "Level.h"
#include <iostream>
#include <SFML/Audio.hpp>
Level::Level(Grafix& grafix, sf::RenderWindow& window, int numLevel,int prevScore,int prevLive ) :m_window(window),m_grafix(grafix), m_background(grafix.getTexture('B'), { 0,0 }, 'B', {800,800})
,m_informationDisplay(grafix)
{
	m_numLevel = numLevel;
	m_board.editBoard(grafix, *this ,numLevel);
	m_isDiggerMove = false;
	m_digger->setNumDiamond( m_board.getNumDiamond() );
	m_isClosedByUser = false;
	m_gameOver = false;
	m_digger->setNumScores(prevScore + (numLevel -1 )*20);
	m_digger->setNumLive(prevLive);
}
//----------------------------------------------------------------------------
int Level::getTotalLive() {
	return m_digger->getLives();
}
//----------------------------------------------------------------------------


void Level::editDynamicObject(char currentChar, Grafix& grafix, sf::Vector2f Point)//����� ������ ��������� �������� 
{																															
	switch (currentChar)
	{
		
	case DIGGER://����� �����
		m_digger = new Digger(grafix.getTexture(currentChar), Point, m_board.getSizeOfShape(),m_timer);
		break;

	case MONSTER:// ����� ������� �� ������� ������
				int c = rand() % 2;//����� ������� ������� ��������� ����� �����
				switch (c)
				{
				case REGULARMONSTER: m_dynamicObject.push_back(new RegularMonster(grafix.getTexture(0), Point, m_board.getSizeOfShape()));
					break;
				case SPECIALMONSTER : m_dynamicObject.push_back(new SpecialMonster (grafix.getTexture(1), Point, m_board.getSizeOfShape()));
				default:
					break;
				}
				
	break;

	}
}
//----------------------------------------------------------------------------
int Level::getTotalScore() {
	return m_digger->getNumScores();
}
//----------------------------------------------------------------------------


void Level::run()//������� ������� �� ���� ���� 
{
	Grafix::getInstance().m_sounds.play();
	float minDeltaTime = 1.f;
	while (m_window.isOpen() &&  m_digger->getNumDiamond() > 0 && !m_gameOver)// ���� ���� �� ��� ����� ����,����� �� ���� ����� �� �� ��������, ����� ����
	{
		
		if (m_timer.getTimer() - m_timer.getCurrentTime() < 0)// ���� ��� ������ ������� ���� ����
			 m_gameOver =true;
		if (m_digger->getNeedToSetBoard()) //�� ���� ����� �� ����
			{
				if (m_digger->getLives() >= 0) //�� ���� ����� ����
				{
						m_isDiggerMove = false;//������ ����� ����� �� ���� �� ������ �����
						std::this_thread::sleep_for(std::chrono::milliseconds(2200));//���� ������ ���� ����� �����  
						int prevLife = m_digger->getLives();// ����� ���� ����� �����  
						deleteDynamicObject();//����� ������� ������ �����
						m_board.editBoard(m_grafix, *this, m_numLevel);//����� ���� ���
						m_digger->setNumLive(prevLife);//������ ���� ����� �� �����
						m_digger->setNumDiamond(m_board.getNumDiamond());
					}
					else// �� �� ���� ����� ���� ��� ������
						m_gameOver=true;
		}
		m_window.clear();//����� ����
		print();
		handlEvent();// ����� �������� ������ ��������
		m_timer.setCurrTime();// ����� �� ���� �������
		if (m_isDiggerMove == true)//�� ���� ����� �� ���� ������ ���� �������� ����� �� �����
		{
			m_digger->move(*this);
		}
		moveMosters();//����� �������� ������� �� ����� �������
		m_timer.setPrev(m_timer.getCurrentTime());//����� ���� ����
		
	}
}
//----------------------------------------------------------------------------
void Level::moveMosters()//������� ������� �� ����� ������� 
{
	m_timer.setDeltaTime();
	for (size_t i = 0; i < m_dynamicObject.size(); i++)
	{
			m_dynamicObject[i]->move(*this);
	}
}

//--------------------------------------------------------------------------------------------
void Level::print() {
	//����� ���� �����
	m_informationDisplay.setStringScore("score: " + std::to_string(m_digger->getNumScores()));
	m_informationDisplay.setStringStone("stone: " + std::to_string(m_digger->getNumStones()));
	m_informationDisplay.setStringtime("Time: " + std::to_string((int)(m_timer.getTimer() - m_timer.getCurrentTime())));
	m_informationDisplay.setStringlife("life: " + std::to_string(m_digger->getLives()));
	m_informationDisplay.setStringlevel("level: " + std::to_string(m_numLevel));
	
	m_background.draw(m_window);//����� ���� 
	m_informationDisplay.draw(m_window);
	m_board.drowBoard(m_window);// ���� �������� ������� �� ���������� �������
	m_digger->draw(m_window);
	for (unsigned i = 0; i < m_dynamicObject.size(); i++)//����� �� ���������� ��������
		m_dynamicObject[i]->draw(m_window);

	m_window.display();//����� �����
}
//-----------------------------------------------------------------------------------------
bool Level::checkArrow(int direction)const//������� �������� ������ ��� �� ������ ��� �� ��� ������
{
	if (sf::Keyboard::Right == direction || sf::Keyboard::Left == direction || sf::Keyboard::Up == direction || sf::Keyboard::Down == direction)
		return true;
	return false;
}
//----------------------------------------------------------------------------

void Level::handlEvent() // ������� ������ ��������
{
	sf::Event event;
	while (m_window.pollEvent(event)){
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (checkArrow(event.key.code) )// ���� ��� ������ ��� �� ���� ������, ���� �����
		{
			m_digger->setDiggerDirection(event.key.code);
			m_isDiggerMove = true;
		}
		else if (event.key.code == sf::Keyboard::Space && m_isDiggerMove)// ���� ��� ������ ��� �� ���� ����, �� ���� �����
			m_isDiggerMove = false;
		break;
	case sf::Event::Closed://�� ������ ��� �� ���� ���� �����
		m_isClosedByUser = true;
		m_window.close();
		break;
	default:
		break;
	}
	}
}
//----------------------------------------------------------------------------
vector<StaticObject*> Level::getNameIfIntersect(sf::FloatRect rect)//����� �� ���������� (��) ������ ���
{
	return m_board.getNameIfIntersect(rect);
}

//------------------------------------------------------------------------------
void Level::handlMonsterCollision(sf::Vector2f nextPos, DynamicObject* currentObject)//������� ������ ������� �� ������ 
{
	vector<StaticObject*> colideObject = getNameIfIntersect(currentObject->getFloatRectWithOfsset(nextPos));//����� ���� ��������� �� ������ ���
	for (size_t i = 0; i < colideObject.size(); i++)//���� �� ������ ����� ����� ����� ������� �� ��� �������� ���
	{
		if (colideObject[i]->getName() == '#' || colideObject[i]->getName() == '@') // �� ������ ����� ���� �� ���� ���� �������� ������� 
		{
			HitFunctionPtr phf = m_collision.lookup(currentObject->getClassName(), colideObject[i]->getClassName());
			if (phf)
				phf(*currentObject, *colideObject[i]);
			return;
		}	
	}
	
	// �� ������ ��� �� ������ ����� �� �����
	if (m_digger->intersection(currentObject->getFloatRectWithOfsset(nextPos))) {
		HitFunctionPtr phf = m_collision.lookup(currentObject->getClassName(), m_digger->getClassName());
		if (phf)
			phf(*currentObject,*m_digger);
	}
	currentObject->changeLocation(nextPos);

}
//---------------------------------------------------------------------------
void Level::handlCollision(sf::Vector2f nextPos, Object* currentObject)//������� ������ ������� �� �����
{
	vector<StaticObject*> colideObject = getNameIfIntersect(currentObject->getFloatRectWithOfsset(nextPos));//����� ���� ��������� �� ������ ���
	for (size_t i = 0; i < colideObject.size(); i++)
	{
		if (colideObject[i]->getName() == '#')//����� �� ��� ����������� ��� ���
			  return;
	}
	for (size_t i = 0; i < colideObject.size(); i++)//����� ������� �� �����
	{
		HitFunctionPtr phf = m_collision.lookup(currentObject->getClassName(), colideObject[i]->getClassName());
		if (phf)
			phf(*currentObject, *colideObject[i]);
	}
	if(m_digger->getCanMove())//�� ����� ���� ����
			m_digger->directMoving(*this);//����� �������� ������ �� �����
	m_digger->setCanMove(true);
}

//---------------------------------------------------------------------------
bool Level::isValid(sf::Vector2f v) const//������� �������� ������� ��� �� ������ �����
{
	sf::Vector2f s2 = m_digger->getSizeOfSprite();
	return (v.x >= 0 && v.x <= 810 && v.y >= 100 && v.y +s2.y <= 810 && (v.x +s2.x)<810);
}



//----------------------------------------------------------------------------

 DynamicObject* Level::getDynamicObject(sf::FloatRect rect)//������� ������ �������� ��� ���������� ��������
{
																						
	for (int i = 0; i < m_dynamicObject.size(); i++)
	{
		if (m_dynamicObject[i]->intersection(rect) &&  m_currentMonster!=m_dynamicObject[i])//����� �� �� ����� ��� ������� ���� ����� ������ �� ����
			return m_dynamicObject[i];//����� ������ �������� ����� ����
	}
	if (m_digger->intersection(rect))//����� ����� �� ����� 
		return m_digger;//����� ����� �����
	return nullptr;
}
 //----------------------------------------------------------------------------
 void Level::deleteDynamicObject() {
	 for (size_t i = 0; i < m_dynamicObject.size(); i++)
	 {
		 delete m_dynamicObject[i];
	 }
	 m_dynamicObject.clear();
	 delete m_digger;
	 m_digger = NULL;
	 
 }
 //----------------------------------------------------------------------------
Level::~Level()
{
	deleteDynamicObject();
	
}
