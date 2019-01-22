#include "stdafx.h"

namespace vEngine {
	RTTI_DEFINITIONS(EngineComponent)

		EngineComponent::EngineComponent()
		: m_Engine(nullptr), m_Enabled(true)
	{
	}

	EngineComponent::EngineComponent(Engine& engine)
		: m_Engine(&engine), m_Enabled(true)
	{
	}

	EngineComponent::~EngineComponent()
	{
	}

	Engine* EngineComponent::GetEngine()
	{
		return m_Engine;
	}

	void EngineComponent::SetEngine(Engine& engine)
	{
		m_Engine = &engine;
	}

	bool EngineComponent::Enabled() const
	{
		return m_Enabled;
	}

	void EngineComponent::SetEnabled(bool enabled)
	{
		m_Enabled = enabled;
	}

	void EngineComponent::Initialize()
	{
	}

	void EngineComponent::Update(const EngineTime& engineTime)
	{
	}
}