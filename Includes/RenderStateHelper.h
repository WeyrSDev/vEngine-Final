#pragma once
#include "stdafx.h"
namespace vEngine {
	class Engine;
	class RenderStateHelper {
	public:
		RenderStateHelper(Engine& engine);
		~RenderStateHelper();
		//
		static void ResetAll(ID3D11DeviceContext* deviceContext);
		ID3D11RasterizerState* RasterizerState();
		ID3D11BlendState* BlendState();
		ID3D11DepthStencilState* DepthStencilState();
		void SaveRasterizerState();
		void RestoreRasterizerState() const;
		void SaveBlendState();
		void RestoreBlendState() const;
		void SaveDepthStencilState();
		void RestoreDepthStencilState() const;
		void SaveAll();
		void RestoreAll() const;
	private:
		RenderStateHelper(const RenderStateHelper& rhs);
		RenderStateHelper& operator=(const RenderStateHelper& rhs);
	private:
		Engine& m_Engine;
		ID3D11RasterizerState* m_RasterizerState;
		ID3D11BlendState* m_BlendState;
		FLOAT* m_BlendFactor;
		UINT m_SampleMask;
		ID3D11DepthStencilState* m_DepthStencilState;
		UINT m_StencilRef;
	};
}