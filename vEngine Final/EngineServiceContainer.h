#pragma once
#include "stdafx.h"

namespace vEngine {
	class ServiceContainer {
	public:
		ServiceContainer();
		ServiceContainer(const ServiceContainer& rhs) = delete;
		ServiceContainer& operator=(const ServiceContainer& rhs) = delete;

		//
		void AddService(UINT typeID, void* service);
		void RemoveService(UINT typeID);
		void* GetService(UINT typeID) const;
		//
	private:
		//
		std::map<UINT, void*> m_Services;
	};
}