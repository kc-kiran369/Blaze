#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start, m_End;
	std::chrono::duration<float> m_Diff;
public:
	Timer()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{

	}
	float Stop()
	{
		m_End = std::chrono::high_resolution_clock::now();
		m_Diff = m_End - m_Start;
		return m_Diff.count()/1000;
	}
};
#endif