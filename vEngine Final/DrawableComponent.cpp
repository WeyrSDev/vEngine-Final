#include "stdafx.h"

namespace vEngine {
	RTTI_DEFINITIONS(DrawableComponent)

		DrawableComponent::DrawableComponent()
		: EngineComponent(), m_Visible(true), m_Camera(nullptr)
	{
	}

	DrawableComponent::DrawableComponent(Engine& engine)
		: EngineComponent(engine), m_Visible(true), m_Camera(nullptr)
	{
	}

	DrawableComponent::DrawableComponent(Engine& engine, Camera& camera)
		: EngineComponent(engine), m_Visible(true), m_Camera(&camera)
	{
	}

	DrawableComponent::~DrawableComponent()
	{
	}

	bool DrawableComponent::Visible() const
	{
		return m_Visible;
	}

	void DrawableComponent::SetVisible(bool visible)
	{
		m_Visible = visible;
	}

	Camera* DrawableComponent::GetCamera()
	{
		return m_Camera;
	}

	void DrawableComponent::SetCamera(Camera* camera)
	{
		m_Camera = camera;
	}

	void DrawableComponent::Draw(const EngineTime& engineTime)
	{
	}
}