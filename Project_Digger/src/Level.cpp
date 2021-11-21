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


void Level::editDynamicObject(char currentChar, Grafix& grafix, sf::Vector2f Point)//טיפול בהכנסת האוביקטים הדינמיים 
{																															
	switch (currentChar)
	{
		
	case DIGGER://הכנסת השחקן
		m_digger = new Digger(grafix.getTexture(currentChar), Point, m_board.getSizeOfShape(),m_timer);
		break;

	case MONSTER:// הכנסת המפלצות אל הווקטור הדינמי
				int c = rand() % 2;//הכנסת המפלצות הרגילות והמיוחדות בצורת הגרלה
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


void Level::run()//פונקציה שאחראית על ריצת השלב 
{
	Grafix::getInstance().m_sounds.play();
	float minDeltaTime = 1.f;
	while (m_window.isOpen() &&  m_digger->getNumDiamond() > 0 && !m_gameOver)// השלב פועל כל עוד החלון פתוח,השחקן לא סיים לאכול את כל היהלומים, ואינו נפסל
	{
		
		if (m_timer.getTimer() - m_timer.getCurrentTime() < 0)// בודק האם השניות שהוקצאו לשלב עברו
			 m_gameOver =true;
		if (m_digger->getNeedToSetBoard()) //אם צריך לאתחל את השלב
			{
				if (m_digger->getLives() >= 0) //אם נשאר לשחקן חיים
				{
						m_isDiggerMove = false;//בתחילת המשחק השחקן לא יזוז עד שתיהיה לחיצה
						std::this_thread::sleep_for(std::chrono::milliseconds(2200));//בגלל איתחול השלב תיהיה המתנה  
						int prevLife = m_digger->getLives();// שמירת מספר החיים שנותר  
						deleteDynamicObject();//מחיקת המפלצות והשחקן מהלוח
						m_board.editBoard(m_grafix, *this, m_numLevel);//פתיחת השלב שוב
						m_digger->setNumLive(prevLife);//עידכון מספר החיים של השחקן
						m_digger->setNumDiamond(m_board.getNumDiamond());
					}
					else// אם לא נשאר לשחקן חיים יצא מהמשחק
						m_gameOver=true;
		}
		m_window.clear();//ניקוי המסך
		print();
		handlEvent();// קריאה לפונקציה שמטפלת באירועים
		m_timer.setCurrTime();// מעדכן את הזמן העכשווי
		if (m_isDiggerMove == true)//אם היתה לחיצה על מקשי הכיוון נקרא לפונקצית תזוזה של השחקן
		{
			m_digger->move(*this);
		}
		moveMosters();//קריאה לפונקציה שאחראית על תזוזת המפלצות
		m_timer.setPrev(m_timer.getCurrentTime());//עדכון הזמן שעבר
		
	}
}
//----------------------------------------------------------------------------
void Level::moveMosters()//פונקציה שאחראית על תזוזת המפלצות 
{
	m_timer.setDeltaTime();
	for (size_t i = 0; i < m_dynamicObject.size(); i++)
	{
			m_dynamicObject[i]->move(*this);
	}
}

//--------------------------------------------------------------------------------------------
void Level::print() {
	//הדפסת הצגת המידע
	m_informationDisplay.setStringScore("score: " + std::to_string(m_digger->getNumScores()));
	m_informationDisplay.setStringStone("stone: " + std::to_string(m_digger->getNumStones()));
	m_informationDisplay.setStringtime("Time: " + std::to_string((int)(m_timer.getTimer() - m_timer.getCurrentTime())));
	m_informationDisplay.setStringlife("life: " + std::to_string(m_digger->getLives()));
	m_informationDisplay.setStringlevel("level: " + std::to_string(m_numLevel));
	
	m_background.draw(m_window);//הדפסת הרקע 
	m_informationDisplay.draw(m_window);
	m_board.drowBoard(m_window);// קורא לפונקציה שמציירת את האובייקטים הסטטיים
	m_digger->draw(m_window);
	for (unsigned i = 0; i < m_dynamicObject.size(); i++)//מצייר את האובייקטים הדינמיים
		m_dynamicObject[i]->draw(m_window);

	m_window.display();//הדפסת החלון
}
//-----------------------------------------------------------------------------------------
bool Level::checkArrow(int direction)const//פונקציה בוליאנית שתחזיר אמת אם המשתמש לחץ על אחד מהחצים
{
	if (sf::Keyboard::Right == direction || sf::Keyboard::Left == direction || sf::Keyboard::Up == direction || sf::Keyboard::Down == direction)
		return true;
	return false;
}
//----------------------------------------------------------------------------

void Level::handlEvent() // פונקציה שמטפלת באירועים
{
	sf::Event event;
	while (m_window.pollEvent(event)){
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (checkArrow(event.key.code) )// בודק האם המשתמש לחץ על חיצי הכיוון, יאשר תזוזה
		{
			m_digger->setDiggerDirection(event.key.code);
			m_isDiggerMove = true;
		}
		else if (event.key.code == sf::Keyboard::Space && m_isDiggerMove)// בודק האם המשתמש לחץ על המקש רווח, לא יאשר תזוזה
			m_isDiggerMove = false;
		break;
	case sf::Event::Closed://אם המשתמש לחץ על סגור יסגר המשחק
		m_isClosedByUser = true;
		m_window.close();
		break;
	default:
		break;
	}
	}
}
//----------------------------------------------------------------------------
vector<StaticObject*> Level::getNameIfIntersect(sf::FloatRect rect)//מחזיר את האובייקטים (תו) במיקום הבא
{
	return m_board.getNameIfIntersect(rect);
}

//------------------------------------------------------------------------------
void Level::handlMonsterCollision(sf::Vector2f nextPos, DynamicObject* currentObject)//פונקציה שבודקת התנגשות של מפלצות 
{
	vector<StaticObject*> colideObject = getNameIfIntersect(currentObject->getFloatRectWithOfsset(nextPos));//מחזיר איזה אובייקטים יש במיקום הבא
	for (size_t i = 0; i < colideObject.size(); i++)//עובר על הוקטור מכיון שיכול להיות התנגשות עם כמה אוביקטים יחד
	{
		if (colideObject[i]->getName() == '#' || colideObject[i]->getName() == '@') // אם המפלצת נפגשה בקיר או באבן נקרא לפונקצית התנגשות 
		{
			HitFunctionPtr phf = m_collision.lookup(currentObject->getClassName(), colideObject[i]->getClassName());
			if (phf)
				phf(*currentObject, *colideObject[i]);
			return;
		}	
	}
	
	// אם המיקום הבא של המפלצת יחתוך את הדיגר
	if (m_digger->intersection(currentObject->getFloatRectWithOfsset(nextPos))) {
		HitFunctionPtr phf = m_collision.lookup(currentObject->getClassName(), m_digger->getClassName());
		if (phf)
			phf(*currentObject,*m_digger);
	}
	currentObject->changeLocation(nextPos);

}
//---------------------------------------------------------------------------
void Level::handlCollision(sf::Vector2f nextPos, Object* currentObject)//פונקציה שבודקת התנגשות של השחקן
{
	vector<StaticObject*> colideObject = getNameIfIntersect(currentObject->getFloatRectWithOfsset(nextPos));//מחזיר איזה אובייקטים יש במיקום הבא
	for (size_t i = 0; i < colideObject.size(); i++)
	{
		if (colideObject[i]->getName() == '#')//בדיקה אם אחד מהאובייקטים הוא קיר
			  return;
	}
	for (size_t i = 0; i < colideObject.size(); i++)//בדיקת התנגשות של השחקן
	{
		HitFunctionPtr phf = m_collision.lookup(currentObject->getClassName(), colideObject[i]->getClassName());
		if (phf)
			phf(*currentObject, *colideObject[i]);
	}
	if(m_digger->getCanMove())//אם השחקן יכול לזוז
			m_digger->directMoving(*this);//קריאה לפונקציה שמזיזה את השחקן
	m_digger->setCanMove(true);
}

//---------------------------------------------------------------------------
bool Level::isValid(sf::Vector2f v) const//פונקציה בוליאנית שמחזירה אמת אם המיקום בתחום
{
	sf::Vector2f s2 = m_digger->getSizeOfSprite();
	return (v.x >= 0 && v.x <= 810 && v.y >= 100 && v.y +s2.y <= 810 && (v.x +s2.x)<810);
}



//----------------------------------------------------------------------------

 DynamicObject* Level::getDynamicObject(sf::FloatRect rect)//פונקציה שמטפלת בחיתוכים בין האובייקטים הדינמיים
{
																						
	for (int i = 0; i < m_dynamicObject.size(); i++)
	{
		if (m_dynamicObject[i]->intersection(rect) &&  m_currentMonster!=m_dynamicObject[i])//בדיקה אם יש חיתוך בין המפלצות מלבד חיתוך המפלצת עם עצמה
			return m_dynamicObject[i];//החזרת המצביע לאובייקט שאיתו נחתך
	}
	if (m_digger->intersection(rect))//בדיקת חיתוך עם השחקן 
		return m_digger;//החזרת מצביע לשחקן
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
