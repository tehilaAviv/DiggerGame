#pragma once
#include <SFML/Graphics.hpp>
class Timer
{
public:
	Timer();
	void setPrev(float a) { m_prevTime = a; }
	void setCurrTime() { m_currentTime = m_clock2.getElapsedTime().asSeconds(); }
	float getCurrentTime() { return m_currentTime; }
	float getPrevTime() { return m_prevTime; }
	void setDeltaTime() { m_deltaTime = m_clock.restart().asSeconds(); }//  m_deltaTime ������� ������ ������  
	float getDeltaTime()const { return m_deltaTime; }
	float getTimer()const { return m_timer; }//����� ���� 
	void setTime(float a) { m_timer = a; }
	float addingMoreTimer() { return m_timer+=30; }
	~Timer();

private:
	sf::Clock m_clock2;
	sf::Clock m_clock;
	float m_currentTime;
	float m_prevTime;//��� ����� �� ���� ���� 
	float m_deltaTime;//  ��� ����� �� ������� �� ����
	float m_timer;
};