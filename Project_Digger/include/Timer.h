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
	void setDeltaTime() { m_deltaTime = m_clock.restart().asSeconds(); }//  m_deltaTime פונקצית איתחול למשתנה  
	float getDeltaTime()const { return m_deltaTime; }
	float getTimer()const { return m_timer; }//החזרת הזמן 
	void setTime(float a) { m_timer = a; }
	float addingMoreTimer() { return m_timer+=30; }
	~Timer();

private:
	sf::Clock m_clock2;
	sf::Clock m_clock;
	float m_currentTime;
	float m_prevTime;//שדה המכיל את הזמן שעבר 
	float m_deltaTime;//  שדה המכיל את האיתחול של הזמן
	float m_timer;
};