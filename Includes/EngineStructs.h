#pragma once
#include "stdafx.h"

namespace vEngine {


	struct VertexPositionColor
	{
		XMFLOAT4 Position;
		XMFLOAT4 Color;

		VertexPositionColor() { }

		VertexPositionColor(const XMFLOAT4& position, const XMFLOAT4& color)
			: Position(position), Color(color) { }
	};



}