#include "stdafx.h"

namespace vEngine {

	RTTI_DEFINITIONS(Keyboard)

	Keyboard::Keyboard(Engine& engine, LPDIRECTINPUT8 directInput)
		: EngineComponent(engine), m_DirectInput(directInput), m_Device(nullptr)
	{
		assert(m_DirectInput != nullptr);
		ZeroMemory(m_CurrentState, sizeof(m_CurrentState));
		ZeroMemory(m_LastState, sizeof(m_LastState));
	}

	Keyboard::~Keyboard()
	{
		if (m_Device != nullptr)
		{
			m_Device->Unacquire();
			m_Device->Release();
			m_Device = nullptr;
		}
	}

	const byte* const Keyboard::CurrentState() const
	{
		return m_CurrentState;
	}

	const byte* const Keyboard::LastState() const
	{
		return m_LastState;
	}

	void Keyboard::Initialize()
	{
		if (FAILED(m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Device, nullptr)))
		{
			throw EngineException("IDIRECTINPUT8::CreateDevice() failed");
		}

		if (FAILED(m_Device->SetDataFormat(&c_dfDIKeyboard)))
		{
			throw EngineException("IDIRECTINPUTDEVICE8::SetDataFormat() failed");
		}

		if (FAILED(m_Device->SetCooperativeLevel(m_Engine->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			throw EngineException("IDIRECTINPUTDEVICE8::SetCooperativeLevel() failed");
		}

		m_Device->Acquire();
	}

	void Keyboard::Update(const EngineTime& engineTime)
	{
		if (m_Device != nullptr)
		{
			memcpy(m_LastState, m_CurrentState, sizeof(m_CurrentState));

			if (FAILED(m_Device->GetDeviceState(sizeof(m_CurrentState), (LPVOID)m_CurrentState)))
			{
				// Try to reaqcuire the device
				if (SUCCEEDED(m_Device->Acquire()))
				{
					m_Device->GetDeviceState(sizeof(m_CurrentState), (LPVOID)m_CurrentState);
				}
			}
		}
	}

	bool Keyboard::IsKeyUp(byte key) const
	{
		return ((m_CurrentState[key] & 0x80) == 0);
	}

	bool Keyboard::IsKeyDown(byte key) const
	{
		return ((m_CurrentState[key] & 0x80) != 0);
	}

	bool Keyboard::WasKeyUp(byte key) const
	{
		return ((m_LastState[key] & 0x80) == 0);
	}

	bool Keyboard::WasKeyDown(byte key) const
	{
		return ((m_LastState[key] & 0x80) != 0);
	}

	bool Keyboard::WasKeyPressedThisFrame(byte key) const
	{
		return (IsKeyDown(key) && WasKeyUp(key));
	}

	bool Keyboard::WasKeyReleasedThisFrame(byte key) const
	{
		return (IsKeyUp(key) && WasKeyDown(key));
	}

	bool Keyboard::IsKeyHeldDown(byte key) const
	{
		return (IsKeyDown(key) && WasKeyDown(key));
	}
}