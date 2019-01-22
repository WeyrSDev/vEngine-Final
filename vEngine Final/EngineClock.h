#pragma once
#include "stdafx.h"

namespace vEngine {
	class EngineTime;
	class EngineClock final {
	public:
		EngineClock();
		EngineClock(const EngineClock&) = delete;
		EngineClock& operator=(const EngineClock&) = delete;
		EngineClock(EngineClock&&) = delete;
		EngineClock& operator=(EngineClock&&) = delete;
		~EngineClock() = default;

		//
		const LARGE_INTEGER& StartTime() const;
		const LARGE_INTEGER& CurrentTime() const;
		const LARGE_INTEGER& LastTime() const;
		//
		double GetFrequency() const;
		void Reset();
		void GetTime(LARGE_INTEGER& time);
		void UpdateEngineTime(EngineTime& engineTime);
		//
	private:
		//
		double m_Frequency;
		LARGE_INTEGER m_StartTime;
		LARGE_INTEGER m_CurrentTime;
		LARGE_INTEGER m_LastTime;
		//
	};
}