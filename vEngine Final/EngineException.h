#pragma once
#include "stdafx.h"

namespace vEngine {
	class EngineException : public std::exception {
	public:
		EngineException(const char* const& message, HRESULT hr = S_OK);
		//
		HRESULT HResult() const;
		std::wstring WString() const;
		std::basic_string<TCHAR> ErrorMessage() const;
		//
	private:
		//
		HRESULT m_HResult;
		//
	};

	inline void ThrowIfBroke(HRESULT hr, const char* const& message = "")
	{
		if (FAILED(hr))
		{
			throw EngineException(message, hr);
		}
	}
}