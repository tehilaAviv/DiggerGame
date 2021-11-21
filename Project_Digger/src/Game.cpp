#include "Game.h"

Game::Game(sf::RenderWindow& w, Grafix& g)
	:m_window(w), m_backgroundGameOver(g.getTexture('G'), { 0,0 }, 'G', { 800,800 }),
	m_backgroundWin(g.getTexture('W'), { 0,0 }, 'W', { 800,800 })

{
}
void Game::manage(Grafix& grafix)// פונקציה שמריצה את המשחק
{
	int score = 0;
	int life = 2;
	for (size_t i = 0; i < NUMOFLEVELS; i++)
	{
		score = score + i * 20;
		Level l(grafix, m_window, i + 1, score,life);
		l.run();
		score += l.getTotalScore();
		life = l.getTotalLive();
		if (l.isClosed())
			return;
		if (l.getGameOver()) {
			show();
			return;
		}
		
	}
	showWin();
}
void Game::showWin() {
	m_window.clear();
	m_backgroundWin.draw(m_window);
	m_window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
void Game::show() {
	m_window.clear();
	m_backgroundGameOver.draw(m_window);
	m_window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
Game::~Game()
{
}