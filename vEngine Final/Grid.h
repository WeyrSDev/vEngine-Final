#pragma once
#include "stdafx.h"
namespace vEngine {

	//struct VertexPositionColor;

	class Grid : public DrawableComponent {
		RTTI_DECLARATIONS(Grid, DrawableComponent)
	public:
		Grid(Engine& engine, Camera& camera);
		Grid(Engine& engine, Camera& camera, UINT size, UINT scale, const XMFLOAT4& color);
		~Grid();
		//
		const XMFLOAT3& Position() const;
		const XMFLOAT4 Color() const;
		const UINT Size() const;
		const UINT Scale() const;
		//
		void SetPosition(const XMFLOAT3& position);
		void SetPosition(float x, float y, float z);
		void SetColor(const XMFLOAT4& color);
		void SetSize(UINT size);
		void SetScale(UINT scale);
		//
		virtual void Initialize() override;
		virtual void Draw(const EngineTime& engineTime) override;
	private:
		struct VertexCBufferPerObject {
			XMFLOAT4X4 WorldViewProjection;

			VertexCBufferPerObject() : WorldViewProjection() { }
			VertexCBufferPerObject(const XMFLOAT4X4& wvp) : WorldViewProjection(wvp) { }
		};
	private:
		void InitializeGrid();
	private:
		static const UINT DefaultSize;
		static const UINT DefaultScale;
		static const XMFLOAT4 DefaultColor;
	private:
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;
		ID3D11InputLayout* m_InputLayout;
		ID3D11Buffer* m_VertexBuffer;
		ID3D11Buffer* m_VertexCBufferPerObject;
		VertexCBufferPerObject m_VertexCBufferPerObjectData;
		XMFLOAT3 m_Position;
		UINT m_Size;
		UINT m_Scale;
		XMFLOAT4 m_Color;
		XMFLOAT4X4 m_WorldMatrix;
	private:
		Grid();
		Grid(const Grid& rhs);
		Grid& operator=(const Grid& rhs);
	};
}