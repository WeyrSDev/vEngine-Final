#pragma once
#include "stdafx.h"

namespace DirectX {
	class SpriteBatch;
	class SpriteFont;
}

namespace vEngine {
	class FramesPerSecond : public DrawableComponent
	{
		RTTI_DECLARATIONS(FramesPerSecond, DrawableComponent)

	public:
		FramesPerSecond(Engine& engine);
		~FramesPerSecond();

		XMFLOAT2& TextPosition();
		int FrameRate() const;

		virtual void Initialize() override;
		virtual void Update(const EngineTime& engineTime) override;
		virtual void Draw(const EngineTime& engineTime) override;

	private:
		FramesPerSecond();
		FramesPerSecond(const FramesPerSecond& rhs);
		FramesPerSecond& operator=(const FramesPerSecond& rhs);

		SpriteBatch* m_SpriteBatch;
		SpriteFont* m_SpriteFont;
		XMFLOAT2 m_TextPosition;

		int m_FrameCount;
		int m_FrameRate;
		double m_LastTotalElapsedTime;
	};
}