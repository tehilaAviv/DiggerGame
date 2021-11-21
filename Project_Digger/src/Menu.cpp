#include "Menu.h"
#include "Game.h"
//���� ������ 
Menu::Menu(Grafix& grafix, sf::RenderWindow& window) :m_window(window),m_background(grafix.getTexture('7'), {0,0}, '7', {800,800})//, m_gameOver(grafix.getTexture(GAMEOVER), { 100,100 }, GAMEOVER, { 500,500 })
{
	float y = 300;
	for (int i = 0, index = 8; i < 2;index++, i++)
	{
		sf::Vector2f location;
		sf::Vector2i size;
	  if (index == 8 )
		{
			location = { 400,400 };
			size = { 300,100 };
		}

		
	  else if (index == 9)
		{
			location = { 400,520 };
			size = { 300,100 };
		}
	
		m_buttonOfMenu.push_back(Button(grafix.getTexture((char)index), location, size));//����� �������� ���� ����� �� �������
	}

}


void Menu::handlMenu(sf::RenderWindow& window, Grafix& grafix)//������� ������� �� ����� ���� ������
{

	while (window.isOpen())
	{
		window.clear();
		drawMenu();
		window.display();
		handlEvent(grafix);// ���� ������ ������
	}
}

void Menu::handlEvent(Grafix& grafix)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// �� ������ ��� �� ����
		if (event.type == sf::Event::Closed || event.type == sf::Keyboard::Escape)
		{
			m_window.close();
			return;
		}
		switch (event.type)
		{ 
		case sf::Event::MouseButtonPressed:
			{
				sf::Vector2f mouseClicked = { (float)event.mouseButton.x,(float)event.mouseButton.y };
				for (size_t i = 0; i < m_buttonOfMenu.size(); i++)
				{
					if(m_buttonOfMenu[i].contain(mouseClicked)){//�� ����� ������ ���� �� ����� ���
							switch (i)
							{
							case 0://���� �����
								
							{
								Game game(m_window, grafix);
								game.manage(grafix);
							}
									break;
							case 1:  m_window.close();//�� ���� �� ����� ����� ����
										  return; 
									  break;
							default:
								break;
							}
					break;
					}
						
				}

			}
		}
	}
}



void  Menu::drawMenu()const//������� ������� �� ���� �� ������, ��������� 
{
	m_background.draw(m_window);

	for (int i = 0; i < m_buttonOfMenu.size(); i++)

		m_buttonOfMenu[i].draw(m_window);

}


Menu::~Menu()
{
}
