#include "stdafx.h"

namespace vEngine {
	EngineTime::EngineTime()
		: m_TotalEngineTime(0.0), m_ElapsedEngineTime(0.0)
	{
	}
	double EngineTime::TotalEngineTime() const
	{
		return m_TotalEngineTime;
	}
	double EngineTime::ElapsedEngineTime() const
	{
		return m_ElapsedEngineTime;
	}
	void EngineTime::SetTotalEngineTime(double totalEngineTime)
	{
		m_TotalEngineTime = totalEngineTime;
	}
	void EngineTime::SetElapsedEngineTime(double elapsedEngineTime)
	{
		m_ElapsedEngineTime = elapsedEngineTime;
	}
}
