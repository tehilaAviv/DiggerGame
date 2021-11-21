#include "Board.h"
#include "Level.h"
#include <string>

Board::Board()
{
}
void Board::editBoard(Grafix& grafix, Level& l, int numLevel)
{	
	
	std::ifstream level;
	std::string path = "Level" + std::to_string(numLevel) + ".txt";
	level.open(path);// פתיחת השלב הנוכחי
	if (! level.is_open())
		return;
	
	int sizeRows, sizeCols,numOfStones, sizeObjectX, sizeObjectY;
	float gameTime;
	level >> sizeRows >> sizeCols>> numOfStones>>gameTime;	
	l.setTimer(gameTime);
	//חילוק של הלוח
	clear();
	sizeObjectX = 800 / sizeCols + 1;
	sizeObjectY = 700 / sizeRows + 1;
	m_sizeOfShape = { sizeObjectX , sizeObjectY };
	char currentChar = level.get();//קריאת תו מקובץ
	for (int i = 0, y = 100; i < sizeRows; y += sizeObjectY, i++)
	{
		int j = 0, x =0;
		std::vector<StaticObject*> column;// וקטור עזר
		while (j < sizeCols)
		{
			char currentChar = level.get();// קריאת התוים אחד אחרי השני
			if (currentChar != '\n')// בדיקה אם אנו עדין לא בסוף השורה
			{
				switch (checkTypeObject(currentChar))//בדיקה אם התו הינו דינמי או סטטי
				{
				case 's':// הכנסת האוביקטים הסטטיים
					if (currentChar == '+') {
						int key = rand() % 3;	
						column.push_back(new Gift(grafix.getTexture(currentChar), sf::Vector2f{ (float)x,(float)y }, currentChar, getSizeOfShape(), key));
					}
					else if (currentChar == '@') {
						column.push_back(new Stone(grafix.getTexture(currentChar), sf::Vector2f{ (float)x,(float)y }, currentChar, getSizeOfShape()));
					}
					else if (currentChar == 'D') {
						column.push_back(new Diamond(grafix.getTexture(currentChar), sf::Vector2f{ (float)x,(float)y }, currentChar, getSizeOfShape()));
					}
					else if (currentChar == '#') {
						column.push_back(new Wall(grafix.getTexture(currentChar), sf::Vector2f{ (float)x,(float)y }, currentChar, getSizeOfShape()));
					}
					else
						column.push_back(new StaticObject(grafix.getTexture(currentChar), sf::Vector2f{ (float)x,(float)y }, currentChar, getSizeOfShape()));
					break;
 				case 'd':// הכנסת האוביקטים הדינמיים 
					l.editDynamicObject(currentChar, grafix, sf::Vector2f{ (float)x,(float)y });
					column.push_back(new StaticObject(grafix.getTexture(' '), sf::Vector2f{ (float)x,(float)y }, ' ', getSizeOfShape()));
					break;
				default:
					break;
				}
				x += sizeObjectX; j++;
			}
		}
		m_editBoard.push_back(column);

	}
	l.setDiggerStone(numOfStones);
	
	level.close();
}



void Board::clear() //פונקציה זו אחראית על הניקוי
{
	for (int i = 0; i < m_editBoard.size(); i++)
	{
		for (int j = 0; j < m_editBoard[i].size(); j++)
			delete m_editBoard[i][j];
	}
	m_editBoard.clear();
}

void Board::drowBoard(sf::RenderWindow& window)//פונקציה זו אחראית לצייר האוביקטים על הלוח
{
	for (size_t i = 0; i < m_editBoard.size(); i++)
	{
		for (size_t j = 0; j < m_editBoard[i].size(); j++) {
			if (m_editBoard[i][j]->getName() != ' ')
				m_editBoard[i][j]->draw(window);
		}
		
	}
}

//--------------------------------------------------------------------------------
char Board::checkTypeObject(char c)const
{
	if (c == '@'||c=='#'||c=='+'||c=='D'||c==' ')
		return 's';
	else if(c=='/'||c=='!')
		return 'd';
	return ' ';
}

//--------------------------------------------------------------------------------
sf::Vector2i  Board::getSizeOfShape()const
{
	return m_sizeOfShape;
}
//--------------------------------------------------------------------------------

vector<StaticObject*> Board::getNameIfIntersect(sf::FloatRect rect)// פונקציה המחזירה את האובייקטים בו האוביקט הדינמי נפגש 
{
	vector <StaticObject*> ret;
	for (size_t i = 0; i < m_editBoard.size(); i++)
	{
		for (size_t j = 0; j < m_editBoard[i].size(); j++)
		{
			if ( m_editBoard[i][j]->intersection(rect) && m_editBoard[i][j]->getName()!=' ')//בדיקה אם יש חיתוך בין האובייקטים מלבד רווח,אם כן נחזיר את תו האוביקט
				 ret.push_back (m_editBoard[i][j]);
		}
	}
	return ret;
}


//--------------------------------------------------------------------------------
int Board::getNumDiamond()//פונקציה שסופרת כמה יהלומים יש בלוח
{
	int counter = 0;
	for (int i = 0; i < m_editBoard.size(); i++)
	{
		for (int j = 0; j < m_editBoard[i].size(); j++)
			if (m_editBoard[i][j]->getName() == 'D')
				counter++;
	}
	return counter;
}
//--------------------------------------------------------------------------------



Board::~Board()
{
	// מוחק את הקצאת המצביע
	for (int i = 0; i < m_editBoard.size(); i++)
	{
		for (int j = 0; j < m_editBoard[i].size(); j++)
			delete m_editBoard[i][j];
	}
	
}