#pragma once
#include "stdafx.h"

namespace vEngine {
	class Keyboard : public EngineComponent {
		RTTI_DECLARATIONS(Keyboard, EngineComponent)
	public:
		Keyboard(Engine& engine, LPDIRECTINPUT8 directInput);
		~Keyboard();
		//
		const byte* const CurrentState() const;
		const byte* const LastState() const;
		//
		virtual void Initialize() override;
		virtual void Update(const EngineTime& engineTime) override;
		//
		bool IsKeyUp(byte key) const;
		bool IsKeyDown(byte key) const;
		bool WasKeyUp(byte key) const;
		bool WasKeyDown(byte key) const;
		bool WasKeyPressedThisFrame(byte key) const;
		bool WasKeyReleasedThisFrame(byte key) const;
		bool IsKeyHeldDown(byte key) const;
	private:
		Keyboard();
		Keyboard(const Keyboard& rhs);
	private:
		static const int KeyCount = 256;
	private:
		LPDIRECTINPUT8 m_DirectInput;
		LPDIRECTINPUTDEVICE8 m_Device;
		byte m_CurrentState[KeyCount];
		byte m_LastState[KeyCount];
	};
}