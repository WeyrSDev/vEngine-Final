#include "stdafx.h"
using namespace DirectX;

namespace vEngine {
	RTTI_DEFINITIONS(OrthographicCamera)

	const float OrthographicCamera::DefaultViewWidth = 100.0f;
	const float OrthographicCamera::DefaultViewHeight = 100.0f;

	OrthographicCamera::OrthographicCamera(Engine& engine, float viewWidth, float viewHeight, float nearPlaneDistance, float farPlaneDistance) :
		Camera(engine, nearPlaneDistance, farPlaneDistance),
		m_ViewWidth(viewWidth), m_ViewHeight(viewHeight)
	{
	}

	float OrthographicCamera::ViewWidth() const
	{
		return m_ViewWidth;
	}

	void OrthographicCamera::SetViewWidth(float viewWidth)
	{
		if (viewWidth > 0.0f)
		{
			m_ViewWidth = viewWidth;
		}
	}

	float OrthographicCamera::ViewHeight() const
	{
		return m_ViewHeight;
	}

	void OrthographicCamera::SetViewHeight(float viewHeight)
	{
		if (viewHeight > 0.0f)
		{
			m_ViewHeight = viewHeight;
		}
	}
	void OrthographicCamera::UpdateProjectionMatrix()
	{
		XMMATRIX projectionMatrix = XMMatrixOrthographicRH(m_ViewWidth, m_ViewHeight, m_NearPlaneDistance, m_FarPlaneDistance);
		XMStoreFloat4x4(&m_ProjectionMatrix, projectionMatrix);
	}
}
