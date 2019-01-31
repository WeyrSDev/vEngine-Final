#include "stdafx.h"
namespace vEngine {
	RTTI_DEFINITIONS(FirstPersonCamera)

	const float FirstPersonCamera::DefaultRotationRate = XMConvertToRadians(1.0f);
	const float FirstPersonCamera::DefaultMovementRate = 10.0f;
	const float FirstPersonCamera::DefaultMouseSensitivity = 100.0f;

	FirstPersonCamera::FirstPersonCamera(Engine& engine)
		: Camera(engine), m_Keyboard(nullptr), m_Mouse(nullptr),
		m_MouseSensitivity(DefaultMouseSensitivity), m_RotationRate(DefaultRotationRate), m_MovementRate(DefaultMovementRate)
	{
	}

	FirstPersonCamera::FirstPersonCamera(Engine& engine, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
		: Camera(engine, fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance), m_Keyboard(nullptr), m_Mouse(nullptr),
		m_MouseSensitivity(DefaultMouseSensitivity), m_RotationRate(DefaultRotationRate), m_MovementRate(DefaultMovementRate)

	{
	}

	FirstPersonCamera::~FirstPersonCamera()
	{
		m_Keyboard = nullptr;
		m_Mouse = nullptr;
	}

	const Keyboard& FirstPersonCamera::GetKeyboard() const
	{
		return *m_Keyboard;
	}

	void FirstPersonCamera::SetKeyboard(Keyboard& keyboard)
	{
		m_Keyboard = &keyboard;
	}

	const Mouse& FirstPersonCamera::GetMouse() const
	{
		return *m_Mouse;
	}

	void FirstPersonCamera::SetMouse(Mouse& mouse)
	{
		m_Mouse = &mouse;
	}

	float&FirstPersonCamera::MouseSensitivity()
	{
		return m_MouseSensitivity;
	}


	float& FirstPersonCamera::RotationRate()
	{
		return m_RotationRate;
	}

	float& FirstPersonCamera::MovementRate()
	{
		return m_MovementRate;
	}

	void FirstPersonCamera::Initialize()
	{
		m_Keyboard = (Keyboard*)m_Engine->Services().GetService(Keyboard::TypeIdClass());
		m_Mouse = (Mouse*)m_Engine->Services().GetService(Mouse::TypeIdClass());

		Camera::Initialize();
	}

	void FirstPersonCamera::Update(const EngineTime& engineTime)
	{
		XMFLOAT2 movementAmount = Vector2Helper::Zero;
		if (m_Keyboard != nullptr)
		{
			if (m_Keyboard->IsKeyDown(DIK_W))
			{
				movementAmount.y = 1.0f;
			}

			if (m_Keyboard->IsKeyDown(DIK_S))
			{
				movementAmount.y = -1.0f;
			}

			if (m_Keyboard->IsKeyDown(DIK_A))
			{
				movementAmount.x = -1.0f;
			}

			if (m_Keyboard->IsKeyDown(DIK_D))
			{
				movementAmount.x = 1.0f;
			}
		}

		XMFLOAT2 rotationAmount = Vector2Helper::Zero;
		if ((m_Mouse != nullptr) && (m_Mouse->IsButtonHeldDown(MouseButtonsLeft)))
		{
			LPDIMOUSESTATE mouseState = m_Mouse->CurrentState();
			rotationAmount.x = -mouseState->lX * m_MouseSensitivity;
			rotationAmount.y = -mouseState->lY * m_MouseSensitivity;
		}

		float elapsedTime = (float)engineTime.ElapsedEngineTime();
		XMVECTOR rotationVector = XMLoadFloat2(&rotationAmount) * m_RotationRate * elapsedTime;
		XMVECTOR right = XMLoadFloat3(&m_Right);

		XMMATRIX pitchMatrix = XMMatrixRotationAxis(right, XMVectorGetY(rotationVector));
		XMMATRIX yawMatrix = XMMatrixRotationY(XMVectorGetX(rotationVector));

		ApplyRotation(XMMatrixMultiply(pitchMatrix, yawMatrix));

		XMVECTOR position = XMLoadFloat3(&m_Position);
		XMVECTOR movement = XMLoadFloat2(&movementAmount) * m_MovementRate * elapsedTime;

		XMVECTOR strafe = right * XMVectorGetX(movement);
		position += strafe;

		XMVECTOR forward = XMLoadFloat3(&m_Direction) * XMVectorGetY(movement);
		position += forward;

		XMStoreFloat3(&m_Position, position);

		Camera::Update(engineTime);
	}
}
