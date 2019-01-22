#pragma once
#include "stdafx.h"

namespace vEngine {
	class Engine;
	class EngineTime;
	class EngineComponent : public RTTI {
		RTTI_DECLARATIONS(EngineComponent, RTTI)
	public:
		EngineComponent();
		EngineComponent(Engine& engine);
		EngineComponent(const EngineComponent&) = default;
		EngineComponent& operator=(const EngineComponent&) = default;
		virtual ~EngineComponent();

		//
		Engine* GetEngine();
		void SetEngine(Engine& engine);
		bool Enabled() const;
		void SetEnabled(bool enabled);
		//
		virtual void Initialize();
		virtual void Update(const EngineTime& engineTime);
		//
	protected:
		//
		Engine* m_Engine;
		bool m_Enabled;
	};
}