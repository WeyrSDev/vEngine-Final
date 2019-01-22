#pragma once
namespace vEngine {
	class EngineTime {
	public:
		EngineTime();
		//
		double TotalEngineTime() const;
		double ElapsedEngineTime() const;
		void SetTotalEngineTime(double totalEngineTime);
		void SetElapsedEngineTime(double elapsedEngineTime);
		//
	private:
		//
		double m_TotalEngineTime;
		double m_ElapsedEngineTime;
		//
	};
}