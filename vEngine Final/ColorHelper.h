#pragma once
#include "stdafx.h"

namespace vEngine {
	class ColorHelper
	{
	private:
		ColorHelper();
		ColorHelper(const ColorHelper& rhs);
		ColorHelper& operator=(const ColorHelper& rhs);
	public:
		static const XMVECTORF32 Black;
		static const XMVECTORF32 White;
		static const XMVECTORF32 Red;
		static const XMVECTORF32 Green;
		static const XMVECTORF32 Blue;
		static const XMVECTORF32 Yellow;
		static const XMVECTORF32 BlueGreen;
		static const XMVECTORF32 Purple;
		static const XMVECTORF32 CornflowerBlue;
		static const XMVECTORF32 Wheat;
		static const XMVECTORF32 LightGray;
	};
}