#pragma once
#include "stdafx.h"

namespace vEngine {
	class Camera;
	class DrawableComponent : public EngineComponent {
		RTTI_DECLARATIONS(DrawableComponent, EngineComponent)
	public:
		DrawableComponent();
		DrawableComponent(Engine& engine);
		DrawableComponent(Engine& engine, Camera& camera);
		virtual ~DrawableComponent();
		//
		bool Visible() const;
		void SetVisible(bool visible);
		Camera* GetCamera();
		void SetCamera(Camera* camera);
		//
		virtual void Draw(const EngineTime& engineTime);
	protected:
		bool m_Visible;
		Camera* m_Camera;
	private:
		DrawableComponent(const DrawableComponent& rhs);
		DrawableComponent& operator=(const DrawableComponent& rhs);
	};
}