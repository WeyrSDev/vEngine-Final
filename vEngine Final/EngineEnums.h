#pragma once
#include "stdafx.h"

namespace vEngine {
	typedef enum _Flags {
		FLAG1 = (1 << 0),
		FLAG2 = (1 << 1),
		FLAG3 = (1 << 2)
	}Flags;

	typedef enum _MouseButtons {
		MouseButtonsLeft = 0,
		MouseButtonsRight = 1,
		MouseButtonsMiddle = 2,
		MouseButtonsX1 = 3
	}MouseButtons;

	typedef enum class _PadButtons {
		A,
		B,
		X,
		Y,
		LeftStick,
		RightStick,
		LeftShoulder,
		RightShoulder,
		Back,
		Start,
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight
	}PadButtons;
}