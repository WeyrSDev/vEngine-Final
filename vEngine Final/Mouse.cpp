#include "stdafx.h"

namespace vEngine {
	RTTI_DEFINITIONS(Mouse)

	Mouse::Mouse(Engine& engine, LPDIRECTINPUT8 directInput)
		: EngineComponent(engine), m_DirectInput(directInput), m_Device(nullptr), m_XPos(0), m_YPos(0), m_Wheel(0)
	{
		assert(m_DirectInput != nullptr);
		ZeroMemory(&m_CurrentState, sizeof(m_CurrentState));
		ZeroMemory(&m_LastState, sizeof(m_LastState));
	}

	Mouse::~Mouse()
	{
		if (m_Device != nullptr)
		{
			m_Device->Unacquire();
			m_Device->Release();
			m_Device = nullptr;
		}
	}

	LPDIMOUSESTATE Mouse::CurrentState()
	{
		return &m_CurrentState;
	}

	LPDIMOUSESTATE Mouse::LastState()
	{
		return &m_LastState;
	}

	long Mouse::X() const
	{
		return m_XPos;
	}

	long Mouse::Y() const
	{
		return m_YPos;
	}

	long Mouse::Wheel() const
	{
		return m_Wheel;
	}

	void Mouse::Initialize()
	{
		if (FAILED(m_DirectInput->CreateDevice(GUID_SysMouse, &m_Device, nullptr)))
		{
			throw EngineException("IDIRECTINPUT8::CreateDevice() failed");
		}

		if (FAILED(m_Device->SetDataFormat(&c_dfDIMouse)))
		{
			throw EngineException("IDIRECTINPUTDEVICE8::SetDataFormat() failed");
		}

		if (FAILED(m_Device->SetCooperativeLevel(m_Engine->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			throw EngineException("IDIRECTINPUTDEVICE8::SetCooperativeLevel() failed");
		}

		m_Device->Acquire();
	}

	void Mouse::Update(const EngineTime& engineTime)
	{
		if (m_Device != nullptr)
		{
			memcpy(&m_LastState, &m_CurrentState, sizeof(m_CurrentState));

			if (FAILED(m_Device->GetDeviceState(sizeof(m_CurrentState), &m_CurrentState)))
			{
				// Try to reaqcuire the device
				if (SUCCEEDED(m_Device->Acquire()))
				{
					if (FAILED(m_Device->GetDeviceState(sizeof(m_CurrentState), &m_CurrentState)))
					{
						return;
					}
				}
			}

			// Accumulate positions
			m_XPos += m_CurrentState.lX;
			m_YPos += m_CurrentState.lY;
			m_Wheel += m_CurrentState.lZ;
		}
	}

	bool Mouse::IsButtonUp(MouseButtons button) const
	{
		return ((m_CurrentState.rgbButtons[button] & 0x80) == 0);
	}

	bool Mouse::IsButtonDown(MouseButtons button) const
	{
		return ((m_CurrentState.rgbButtons[button] & 0x80) != 0);
	}

	bool Mouse::WasButtonUp(MouseButtons button) const
	{
		return ((m_LastState.rgbButtons[button] & 0x80) == 0);
	}

	bool Mouse::WasButtonDown(MouseButtons button) const
	{
		return ((m_LastState.rgbButtons[button] & 0x80) != 0);
	}

	bool Mouse::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonUp(button));
	}

	bool Mouse::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return (IsButtonUp(button) && WasButtonDown(button));
	}

	bool Mouse::IsButtonHeldDown(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonDown(button));
	}
}