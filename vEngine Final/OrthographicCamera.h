#pragma once
#include "stdafx.h"

namespace vEngine {
	class EngineTime;

	class OrthographicCamera : public Camera {
		RTTI_DECLARATIONS(OrthographicCamera, Camera)
	public:
		explicit OrthographicCamera(Engine& engine, float viewWidth = DefaultViewWidth, float viewHeight = DefaultViewHeight, float nearPlaneDistance = DefaultNearPlaneDistance, float farPlaneDistance = DefaultFarPlaneDistance);
		OrthographicCamera(const OrthographicCamera&) = default;
		OrthographicCamera(OrthographicCamera&&) = default;
		OrthographicCamera& operator=(const OrthographicCamera&) = default;
		OrthographicCamera& operator=(OrthographicCamera&&) = default;
		virtual ~OrthographicCamera() = default;

		float ViewWidth() const;
		void SetViewWidth(float viewWidth);

		float ViewHeight() const;
		void SetViewHeight(float viewHeight);

		virtual void UpdateProjectionMatrix() override;

		static const float DefaultViewWidth;
		static const float DefaultViewHeight;
	protected:
		float m_ViewWidth;
		float m_ViewHeight;
	};
}