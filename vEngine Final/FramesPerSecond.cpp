#include "stdafx.h"

namespace vEngine {
	RTTI_DEFINITIONS(FramesPerSecond)

		FramesPerSecond::FramesPerSecond(Engine& engine)
		: DrawableComponent(engine), m_SpriteBatch(nullptr), m_SpriteFont(nullptr), m_TextPosition(0.0f, 60.0f),
		m_FrameCount(0), m_FrameRate(0), m_LastTotalElapsedTime(0.0)
	{
	}

	FramesPerSecond::~FramesPerSecond()
	{
		DeleteObject(m_SpriteFont);
		DeleteObject(m_SpriteBatch);
	}

	XMFLOAT2& FramesPerSecond::TextPosition()
	{
		return m_TextPosition;
	}

	int FramesPerSecond::FrameRate() const
	{
		return m_FrameCount;
	}

	void FramesPerSecond::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		m_SpriteBatch = new SpriteBatch(m_Engine->Direct3DDeviceContext());
		m_SpriteFont = new SpriteFont(m_Engine->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
	}

	void FramesPerSecond::Update(const EngineTime& engineTime)
	{
		if (engineTime.TotalEngineTime() - m_LastTotalElapsedTime >= 1)
		{
			m_LastTotalElapsedTime = engineTime.TotalEngineTime();
			m_FrameRate = m_FrameCount;
			m_FrameCount = 0;
		}

		m_FrameCount++;
	}

	void FramesPerSecond::Draw(const EngineTime& engineTime)
	{
		m_SpriteBatch->Begin();

		std::wostringstream fpsLabel;
		fpsLabel << std::setprecision(4) << L"Frame Rate: " << m_FrameRate << "    Total Elapsed Time: " << engineTime.TotalEngineTime();
		m_SpriteFont->DrawString(m_SpriteBatch, fpsLabel.str().c_str(), m_TextPosition);

		m_SpriteBatch->End();
	}
}