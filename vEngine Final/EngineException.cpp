#include "stdafx.h"

namespace vEngine {
	EngineException::EngineException(const char * const & message, HRESULT hr)
		: exception(message), m_HResult(hr)
	{
	}
	HRESULT EngineException::HResult() const
	{
		return m_HResult;
	}
	std::wstring EngineException::WString() const
	{
		std::string whatString(what());
		std::wstring whatw;
		whatw.assign(whatString.begin(), whatString.end());
		return whatw;
	}
	std::basic_string<TCHAR> EngineException::ErrorMessage() const
	{
		_com_error error(m_HResult);
		return error.ErrorMessage();
	}

}