#pragma once
#include "stdafx.h"
namespace vEngine {
	class EngineTime;
	class Camera : public EngineComponent {
		RTTI_DECLARATIONS(Camera, EngineComponent)
	public:
		explicit Camera(Engine& engine, float nearPlaneDistance = DefaultNearPlaneDistance, float farPlaneDistance = DefaultFarPlaneDistance);
		Camera(Engine& engine, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		Camera(const Camera&) = default;
		Camera& operator=(const Camera&) = default;
		Camera(Camera&&) = default;
		Camera& operator=(Camera&&) = default;
		virtual ~Camera() = default;
		//
		const XMFLOAT3& Position() const;
		const XMFLOAT3& Direction() const;
		const XMFLOAT3& Up() const;
		const XMFLOAT3& Right() const;
		//
		XMVECTOR PositionVector() const;
		XMVECTOR DirectionVector() const;
		XMVECTOR UpVector() const;
		XMVECTOR RightVector() const;
		//
		float AspectRatio() const;
		float FieldOfView() const;
		float NearPlaneDistance() const;
		float FarPlaneDistance() const;
		//
		XMMATRIX ViewMatrix() const;
		XMMATRIX ProjectionMatrix() const;
		XMMATRIX ViewProjectionMatrix() const;
		//
		virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		virtual void SetPosition(FXMVECTOR position);
		virtual void SetPosition(const XMFLOAT3& position);
		virtual void Reset();
		virtual void Initialize() override;
		virtual void Update(const EngineTime& engineTime) override;
		virtual void UpdateViewMatrix();
		virtual void UpdateProjectionMatrix();
		virtual void ApplyRotation(CXMMATRIX transform);
		virtual void ApplyRotation(const XMFLOAT4X4& transform);
	public:
		static const float DefaultFieldOfView;
		static const float DefaultAspectRatio;
		static const float DefaultNearPlaneDistance;
		static const float DefaultFarPlaneDistance;
	protected:
		float m_FieldOfView;
		float m_AspectRatio;
		float m_NearPlaneDistance;
		float m_FarPlaneDistance;
		//
		XMFLOAT3 m_Position;
		XMFLOAT3 m_Direction;
		XMFLOAT3 m_Up;
		XMFLOAT3 m_Right;
		//
		XMFLOAT4X4 m_ViewMatrix;
		XMFLOAT4X4 m_ProjectionMatrix;
	};
}