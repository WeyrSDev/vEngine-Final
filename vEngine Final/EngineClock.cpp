#include "stdafx.h"

namespace vEngine {
	EngineClock::EngineClock()
		: m_StartTime(), m_CurrentTime(), m_LastTime(), m_Frequency()
	{
		m_Frequency = GetFrequency();
		Reset();
	}
	const LARGE_INTEGER& EngineClock::StartTime() const
	{
		return m_StartTime;
	}
	const LARGE_INTEGER& EngineClock::CurrentTime() const
	{
		return m_CurrentTime;
	}
	const LARGE_INTEGER& EngineClock::LastTime() const
	{
		return m_LastTime;
	}
	double EngineClock::GetFrequency() const
	{
		LARGE_INTEGER frequency;
		if (QueryPerformanceFrequency(&frequency) == false)
		{
			throw std::exception("QueryPerformanceFrequency() failed.");
		}
		return (double)frequency.QuadPart;
	}
	void EngineClock::Reset()
	{
		GetTime(m_StartTime);
		m_CurrentTime = m_StartTime;
		m_LastTime = m_CurrentTime;

	}
	void EngineClock::GetTime(LARGE_INTEGER& time)
	{
		QueryPerformanceCounter(&time);
	}
	void EngineClock::UpdateEngineTime(EngineTime& engineTime)
	{
		GetTime(m_CurrentTime);
		engineTime.SetTotalEngineTime((m_CurrentTime.QuadPart - m_StartTime.QuadPart) / m_Frequency);
		engineTime.SetElapsedEngineTime((m_CurrentTime.QuadPart - m_LastTime.QuadPart) / m_Frequency);
		m_LastTime = m_CurrentTime;
	}
}