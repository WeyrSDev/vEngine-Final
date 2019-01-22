#include "stdafx.h"

namespace vEngine
{
	ServiceContainer::ServiceContainer()
		: m_Services()
	{
	}

	void ServiceContainer::AddService(UINT typeID, void* service)
	{
		m_Services.insert(std::pair<UINT, void*>(typeID, service));
	}


	void ServiceContainer::RemoveService(UINT typeID)
	{
		m_Services.erase(typeID);
	}

	void* ServiceContainer::GetService(UINT typeID) const
	{
		std::map<UINT, void*>::const_iterator it = m_Services.find(typeID);

		return (it != m_Services.end() ? it->second : nullptr);
	}
}
