#pragma once
#include "stdafx.h"

namespace vEngine {
	class EngineTime;
	class Mouse : public EngineComponent {
		RTTI_DECLARATIONS(Mouse, EngineComponent)
	public:
		Mouse(Engine& engine, LPDIRECTINPUT8 directInput);
		~Mouse();
		//
		LPDIMOUSESTATE CurrentState();
		LPDIMOUSESTATE LastState();
		//
		virtual void Initialize() override;
		virtual void Update(const EngineTime& engineTime) override;
		//
		long X() const;
		long Y() const;
		long Wheel() const;
		//
		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;
		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;
		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;
		bool IsButtonHeldDown(MouseButtons button) const;
	private:
		Mouse();
	private:
		LPDIRECTINPUT8 m_DirectInput;
		LPDIRECTINPUTDEVICE8 m_Device;
		DIMOUSESTATE m_CurrentState;
		DIMOUSESTATE m_LastState;
		long m_XPos;
		long m_YPos;
		long m_Wheel;
	};
}