#include "stdafx.h"
using namespace std;
using namespace DirectX;

namespace vEngine {
	RTTI_DEFINITIONS(XBoxGamePad)

	unique_ptr<GamePad> XBoxGamePad::sGamePad(new DirectX::GamePad);

	GamePad* XBoxGamePad::GamePad()
	{
		return sGamePad.get();
	}

	XBoxGamePad::XBoxGamePad(Engine& engine, int player) :
		EngineComponent(engine), m_Player(player)
	{
	}

	int XBoxGamePad::Player() const
	{
		return m_Player;
	}

	const GamePad::State& XBoxGamePad::CurrentState() const
	{
		return m_CurrentState;
	}

	const GamePad::State& XBoxGamePad::LastState() const
	{
		return m_LastState;
	}

	void XBoxGamePad::Initialize()
	{
		m_CurrentState = sGamePad->GetState(m_Player);
		m_LastState = m_CurrentState;
	}

	void XBoxGamePad::Update(const EngineTime& engineTime)
	{
		UNREFERENCED_PARAMETER(engineTime);

		m_LastState = m_CurrentState;
		m_CurrentState = sGamePad->GetState(m_Player);
	}

	bool XBoxGamePad::IsButtonUp(PadButtons button) const
	{
		return GetButtonState(m_CurrentState, button) == false;
	}

	bool XBoxGamePad::IsButtonDown(PadButtons button) const
	{
		return GetButtonState(m_CurrentState, button);
	}

	bool XBoxGamePad::WasButtonUp(PadButtons button) const
	{
		return GetButtonState(m_LastState, button) == false;
	}

	bool XBoxGamePad::WasButtonDown(PadButtons button) const
	{
		return GetButtonState(m_LastState, button);
	}

	bool XBoxGamePad::WasButtonPressedThisFrame(PadButtons button) const
	{
		return (IsButtonDown(button) && WasButtonUp(button));
	}

	bool XBoxGamePad::WasButtonReleasedThisFrame(PadButtons button) const
	{
		return (IsButtonUp(button) && WasButtonDown(button));
	}

	bool XBoxGamePad::IsButtonHeldDown(PadButtons button) const
	{
		return (IsButtonDown(button) && WasButtonDown(button));
	}

	bool XBoxGamePad::GetButtonState(const GamePad::State& state, PadButtons button) const
	{
		switch (button)
		{
		case PadButtons::A:
			return state.buttons.a;

		case PadButtons::B:
			return state.buttons.b;

		case PadButtons::X:
			return state.buttons.x;

		case PadButtons::Y:
			return state.buttons.y;

		case PadButtons::LeftStick:
			return state.buttons.leftStick;

		case PadButtons::RightStick:
			return state.buttons.rightStick;

		case PadButtons::LeftShoulder:
			return state.buttons.leftShoulder;

		case PadButtons::RightShoulder:
			return state.buttons.rightShoulder;

		case PadButtons::Back:
			return state.buttons.back;

		case PadButtons::Start:
			return state.buttons.start;

		case PadButtons::DPadUp:
			return state.dpad.up;

		case PadButtons::DPadDown:
			return state.dpad.down;

		case PadButtons::DPadLeft:
			return state.dpad.left;

		case PadButtons::DPadRight:
			return state.dpad.right;

		default:
			throw exception("Invalid GamePadButtons.");
		}
	}
}