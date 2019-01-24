#pragma once
#include "stdafx.h"

namespace vEngine {
	class XBoxGamePad : public EngineComponent {
		RTTI_DECLARATIONS(XBoxGamePad, EngineComponent)
	public:
		static DirectX::GamePad* GamePad();
		XBoxGamePad(Engine& engine, int player = 0);
		//
		int Player() const;
		const DirectX::GamePad::State& CurrentState() const;
		const DirectX::GamePad::State& LastState() const;
		//
		virtual void Initialize() override;
		virtual void Update(const EngineTime& engineTime) override;
		//
		bool IsButtonUp(PadButtons button) const;
		bool IsButtonDown(PadButtons button) const;
		bool WasButtonUp(PadButtons button) const;
		bool WasButtonDown(PadButtons button) const;
		bool WasButtonPressedThisFrame(PadButtons button) const;
		bool WasButtonReleasedThisFrame(PadButtons button) const;
		bool IsButtonHeldDown(PadButtons button) const;
	private:
		static std::unique_ptr<DirectX::GamePad> sGamePad;
	private:
		bool GetButtonState(const DirectX::GamePad::State& state, PadButtons button) const;
	private:
		int m_Player;
		DirectX::GamePad::State m_CurrentState;
		DirectX::GamePad::State m_LastState;
	};
}