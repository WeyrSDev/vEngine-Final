#pragma once
#include "stdafx.h"
namespace vEngine {
	class Keyboard;
	class Mouse;
	class FirstPersonCamera : public Camera {
		RTTI_DECLARATIONS(FirstPersonCamera, Camera)
	public:
		FirstPersonCamera(Engine& engine);
		FirstPersonCamera(Engine& engine, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		virtual ~FirstPersonCamera();
		//
		const Keyboard& GetKeyboard() const;
		void SetKeyboard(Keyboard& keyboard);
		const Mouse& GetMouse() const;
		void SetMouse(Mouse& mouse);
		float& MouseSensitivity();
		float& RotationRate();
		float& MovementRate();
		//
		virtual void Initialize() override;
		virtual void Update(const EngineTime& engineTime) override;
	public:
		static const float DefaultMouseSensitivity;
		static const float DefaultRotationRate;
		static const float DefaultMovementRate;
	protected:
		float m_MouseSensitivity;
		float m_RotationRate;
		float m_MovementRate;
		Keyboard* m_Keyboard;
		Mouse* m_Mouse;
	private:
		FirstPersonCamera(const FirstPersonCamera& rhs);
		FirstPersonCamera& operator=(const FirstPersonCamera& rhs);
	};
}