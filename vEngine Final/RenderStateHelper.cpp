#include "stdafx.h"
namespace vEngine {
	RenderStateHelper::RenderStateHelper(Engine& engine)
		: m_Engine(engine), m_RasterizerState(nullptr), m_BlendState(nullptr), m_BlendFactor(new FLOAT[4]), m_SampleMask(UINT_MAX), m_DepthStencilState(nullptr), m_StencilRef(UINT_MAX)
	{
	}

	RenderStateHelper::~RenderStateHelper()
	{
		ReleaseObject(m_RasterizerState);
		ReleaseObject(m_BlendState);
		ReleaseObject(m_DepthStencilState);
		DeleteObjects(m_BlendFactor);
	}

	void RenderStateHelper::ResetAll(ID3D11DeviceContext* deviceContext)
	{
		deviceContext->RSSetState(nullptr);
		deviceContext->OMSetBlendState(nullptr, nullptr, UINT_MAX);
		deviceContext->OMSetDepthStencilState(nullptr, UINT_MAX);
	}

	void RenderStateHelper::SaveRasterizerState()
	{
		ReleaseObject(m_RasterizerState);
		m_Engine.Direct3DDeviceContext()->RSGetState(&m_RasterizerState);
	}

	void RenderStateHelper::RestoreRasterizerState() const
	{
		m_Engine.Direct3DDeviceContext()->RSSetState(m_RasterizerState);
	}

	void RenderStateHelper::SaveBlendState()
	{
		ReleaseObject(m_BlendState);
		m_Engine.Direct3DDeviceContext()->OMGetBlendState(&m_BlendState, m_BlendFactor, &m_SampleMask);
	}

	void RenderStateHelper::RestoreBlendState() const
	{
		m_Engine.Direct3DDeviceContext()->OMSetBlendState(m_BlendState, m_BlendFactor, m_SampleMask);
	}

	void RenderStateHelper::SaveDepthStencilState()
	{
		ReleaseObject(m_DepthStencilState);
		m_Engine.Direct3DDeviceContext()->OMGetDepthStencilState(&m_DepthStencilState, &m_StencilRef);
	}

	void RenderStateHelper::RestoreDepthStencilState() const
	{
		m_Engine.Direct3DDeviceContext()->OMSetDepthStencilState(m_DepthStencilState, m_StencilRef);
	}

	void RenderStateHelper::SaveAll()
	{
		SaveRasterizerState();
		SaveBlendState();
		SaveDepthStencilState();
	}

	void RenderStateHelper::RestoreAll() const
	{
		RestoreRasterizerState();
		RestoreBlendState();
		RestoreDepthStencilState();
	}
}