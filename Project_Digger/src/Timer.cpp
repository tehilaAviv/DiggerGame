#include "Timer.h"

Timer::Timer()
{
	m_currentTime = m_clock.getElapsedTime().asSeconds();
	m_prevTime = m_clock.getElapsedTime().asSeconds();
}

Timer::~Timer()
{
}
