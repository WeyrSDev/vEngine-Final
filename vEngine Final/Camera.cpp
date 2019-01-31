#include "stdafx.h"
namespace vEngine {
	RTTI_DEFINITIONS(Camera)

	const float Camera::DefaultFieldOfView = XM_PIDIV4;
	const float Camera::DefaultNearPlaneDistance = 0.01f;
	const float Camera::DefaultFarPlaneDistance = 1000.0f;
	Camera::Camera(Engine& engine) :
		EngineComponent(engine), m_FieldOfView(DefaultFieldOfView), m_AspectRatio(engine.AspectRatio()), m_NearPlaneDistance(DefaultNearPlaneDistance),
		m_FarPlaneDistance(DefaultFarPlaneDistance), m_Position(), m_Direction(), m_Up(), m_Right(), m_ViewMatrix(), m_ProjectionMatrix()
	{

	}

	Camera::Camera(Engine& engine, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) :
		EngineComponent(engine), m_FieldOfView(fieldOfView), m_AspectRatio(aspectRatio), m_NearPlaneDistance(nearPlaneDistance), 
		m_FarPlaneDistance(farPlaneDistance), m_Position(), m_Direction(), m_Up(), m_Right(), m_ViewMatrix(), m_ProjectionMatrix()
	{
	}
	Camera::~Camera()
	{
	}
	const XMFLOAT3& Camera::Position() const
	{
		return m_Position;
	}
	const XMFLOAT3& Camera::Direction() const
	{
		return m_Direction;
	}
	const XMFLOAT3& Camera::Up() const
	{
		return m_Up;
	}
	const XMFLOAT3& Camera::Right() const
	{
		return m_Right;
	}
	XMVECTOR Camera::PositionVector() const
	{
		return XMLoadFloat3(&m_Position);
	}
	XMVECTOR Camera::DirectionVector() const
	{
		return XMLoadFloat3(&m_Direction);
	}
	XMVECTOR Camera::UpVector() const
	{
		return XMLoadFloat3(&m_Up);
	}
	XMVECTOR Camera::RightVector() const
	{
		return XMLoadFloat3(&m_Right);
	}
	float Camera::AspectRatio() const
	{
		return m_AspectRatio;
	}
	float Camera::FieldOfView() const
	{
		return m_FieldOfView;

	}
	float Camera::NearPlaneDistance() const
	{
		return m_NearPlaneDistance;
	}
	float Camera::FarPlaneDistance() const
	{
		return m_FarPlaneDistance;
	}
	XMMATRIX Camera::ViewMatrix() const
	{
		return XMLoadFloat4x4(&m_ViewMatrix);
	}
	XMMATRIX Camera::ProjectionMatrix() const
	{
		return XMLoadFloat4x4(&m_ProjectionMatrix);
	}
	XMMATRIX Camera::ViewProjectionMatrix() const
	{
		XMMATRIX viewMatrix = XMLoadFloat4x4(&m_ViewMatrix);
		XMMATRIX projectionMatrix = XMLoadFloat4x4(&m_ProjectionMatrix);

		return XMMatrixMultiply(viewMatrix, projectionMatrix);
	}
	void Camera::ApplyRotation(CXMMATRIX transform)
	{
		XMVECTOR direction = XMLoadFloat3(&m_Direction);
		XMVECTOR up = XMLoadFloat3(&m_Up);

		direction = XMVector3TransformNormal(direction, transform);
		direction = XMVector3Normalize(direction);

		up = XMVector3TransformNormal(up, transform);
		up = XMVector3Normalize(up);

		XMVECTOR right = XMVector3Cross(direction, up);
		up = XMVector3Cross(right, direction);

		XMStoreFloat3(&m_Direction, direction);
		XMStoreFloat3(&m_Up, up);
		XMStoreFloat3(&m_Right, right);

	}
	void Camera::ApplyRotation(const XMFLOAT4X4& transform)
	{
		XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
		ApplyRotation(transformMatrix);
	}
	void Camera::SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
		SetPosition(position);
	}
	void Camera::SetPosition(FXMVECTOR position)
	{
		XMStoreFloat3(&m_Position, position);
	}
	void Camera::SetPosition(const XMFLOAT3& position)
	{
		m_Position = position;
	}
	void Camera::Reset()
	{
		m_Position = Vector3Helper::Zero;
		m_Direction = Vector3Helper::Forward;
		m_Up = Vector3Helper::Up;
		m_Right = Vector3Helper::Right;

		UpdateViewMatrix();
	}
	void Camera::Initialize()
	{
		UpdateProjectionMatrix();
		Reset();
	}
	void Camera::Update(const EngineTime& engineTime)
	{
		UpdateViewMatrix();
	}
	void Camera::UpdateViewMatrix()
	{
		XMVECTOR eyePosition = XMLoadFloat3(&m_Position);
		XMVECTOR direction = XMLoadFloat3(&m_Direction);
		XMVECTOR upDirection = XMLoadFloat3(&m_Up);

		XMMATRIX viewMatrix = XMMatrixLookToRH(eyePosition, direction, upDirection);
		XMStoreFloat4x4(&m_ViewMatrix, viewMatrix);
	}
	void Camera::UpdateProjectionMatrix()
	{
		XMMATRIX projectionMatrix = XMMatrixPerspectiveFovRH(m_FieldOfView, m_AspectRatio, m_NearPlaneDistance, m_FarPlaneDistance);
		XMStoreFloat4x4(&m_ProjectionMatrix, projectionMatrix);
	}
}