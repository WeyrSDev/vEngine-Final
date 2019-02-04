#include "stdafx.h"
namespace vEngine {
	RTTI_DEFINITIONS(Grid)

	const UINT Grid::DefaultSize = 16;
	const UINT Grid::DefaultScale = 16;
	const XMFLOAT4 Grid::DefaultColor = XMFLOAT4(0.961f, 0.871f, 0.702f, 1.0f);

	Grid::Grid(Engine& engine, Camera& camera)
		: DrawableComponent(engine), m_VertexShader(nullptr), m_PixelShader(nullptr), m_InputLayout(nullptr), m_VertexBuffer(nullptr),
		m_VertexCBufferPerObject(nullptr), m_VertexCBufferPerObjectData(),
		m_Position(Vector3Helper::Zero), m_Size(DefaultSize), m_Scale(DefaultScale), m_Color(DefaultColor), m_WorldMatrix(MatrixHelper::Identity)
	{
		m_Camera = &camera;
	}

	Grid::Grid(Engine& engine, Camera& camera, UINT size, UINT scale, const XMFLOAT4& color)
		: DrawableComponent(engine), m_VertexShader(nullptr), m_PixelShader(nullptr), m_InputLayout(nullptr), m_VertexBuffer(nullptr),
		m_VertexCBufferPerObject(nullptr), m_VertexCBufferPerObjectData(),
		m_Position(Vector3Helper::Zero), m_Size(size), m_Scale(scale), m_Color(color), m_WorldMatrix(MatrixHelper::Identity)
	{
		m_Camera = &camera;
	}

	Grid::~Grid()
	{
		ReleaseObject(m_VertexCBufferPerObject)
		ReleaseObject(m_VertexBuffer)
		ReleaseObject(m_InputLayout)
		ReleaseObject(m_PixelShader)
		ReleaseObject(m_VertexShader)
	}

	const XMFLOAT3& Grid::Position() const
	{
		return m_Position;
	}

	const XMFLOAT4 Grid::Color() const
	{
		return m_Color;
	}

	const UINT Grid::Size() const
	{
		return m_Size;
	}

	const UINT Grid::Scale() const
	{
		return m_Scale;
	}

	void Grid::SetPosition(const XMFLOAT3& position)
	{
		m_Position = position;

		XMMATRIX translation = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		XMStoreFloat4x4(&m_WorldMatrix, translation);
	}

	void Grid::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;

		XMMATRIX translation = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		XMStoreFloat4x4(&m_WorldMatrix, translation);
	}

	void Grid::SetColor(const XMFLOAT4& color)
	{
		m_Color = color;
		InitializeGrid();
	}

	void Grid::SetSize(UINT size)
	{
		m_Size = size;
		InitializeGrid();
	}

	void Grid::SetScale(UINT scale)
	{
		m_Scale = scale;
		InitializeGrid();
	}

	void Grid::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		// Load a compiled vertex shader
		std::vector<char> compiledVertexShader;
		Utility::LoadBinaryFile(L"Content\\Effects\\BasicVS.cso", compiledVertexShader);
		ThrowIfBroke(m_Engine->Direct3DDevice()->CreateVertexShader(&compiledVertexShader[0], compiledVertexShader.size(), nullptr, &m_VertexShader), "ID3D11Device::CreatedVertexShader() failed.");

		// Load a compiled pixel shader
		std::vector<char> compiledPixelShader;
		Utility::LoadBinaryFile(L"Content\\Effects\\BasicPS.cso", compiledPixelShader);
		ThrowIfBroke(m_Engine->Direct3DDevice()->CreatePixelShader(&compiledPixelShader[0], compiledPixelShader.size(), nullptr, &m_PixelShader), "ID3D11Device::CreatedPixelShader() failed.");

		// Create an input layout
		D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		ThrowIfBroke(m_Engine->Direct3DDevice()->CreateInputLayout(inputElementDescriptions, ARRAYSIZE(inputElementDescriptions), &compiledVertexShader[0], compiledVertexShader.size(), &m_InputLayout), "ID3D11Device::CreateInputLayout() failed.");

		// Create constant buffers
		D3D11_BUFFER_DESC constantBufferDesc;
		ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));
		constantBufferDesc.ByteWidth = sizeof(m_VertexCBufferPerObjectData);
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ThrowIfBroke(m_Engine->Direct3DDevice()->CreateBuffer(&constantBufferDesc, nullptr, &m_VertexCBufferPerObject), "ID3D11Device::CreateBuffer() failed.");

		InitializeGrid();
	}

	void Grid::Draw(const EngineTime& engineTime)
	{
		ID3D11DeviceContext* direct3DDeviceContext = m_Engine->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		direct3DDeviceContext->IASetInputLayout(m_InputLayout);

		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		direct3DDeviceContext->VSSetShader(m_VertexShader, nullptr, 0);
		direct3DDeviceContext->PSSetShader(m_PixelShader, nullptr, 0);

		XMMATRIX worldMatrix = XMLoadFloat4x4(&m_WorldMatrix);
		XMMATRIX wvp = worldMatrix * m_Camera->ViewProjectionMatrix();
		XMStoreFloat4x4(&m_VertexCBufferPerObjectData.WorldViewProjection, XMMatrixTranspose(wvp));

		direct3DDeviceContext->UpdateSubresource(m_VertexCBufferPerObject, 0, nullptr, &m_VertexCBufferPerObjectData, 0, 0);
		direct3DDeviceContext->VSSetConstantBuffers(0, 1, &m_VertexCBufferPerObject);

		direct3DDeviceContext->Draw((m_Size + 1) * 4, 0);
	}

	void Grid::InitializeGrid()
	{
		ReleaseObject(m_VertexBuffer);

		ID3D11Device* direct3DDevice = GetEngine()->Direct3DDevice();
		int length = 4 * (m_Size + 1);
		int size = sizeof(VertexPositionColor) * length;
		std::unique_ptr<VertexPositionColor[]> vertexData(new VertexPositionColor[length]);
		VertexPositionColor* vertices = vertexData.get();

		float adjustedScale = m_Scale * 0.1f;
		float maxPosition = m_Size * adjustedScale / 2;

		for (unsigned int i = 0, j = 0; i < m_Size + 1; i++, j = 4 * i)
		{
			float position = maxPosition - (i * adjustedScale);

			// Vertical line
			vertices[j] = VertexPositionColor(XMFLOAT4(position, 0.0f, maxPosition, 1.0f), m_Color);
			vertices[j + 1] = VertexPositionColor(XMFLOAT4(position, 0.0f, -maxPosition, 1.0f), m_Color);

			// Horizontal line
			vertices[j + 2] = VertexPositionColor(XMFLOAT4(maxPosition, 0.0f, position, 1.0f), m_Color);
			vertices[j + 3] = VertexPositionColor(XMFLOAT4(-maxPosition, 0.0f, position, 1.0f), m_Color);
		}

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.ByteWidth = size;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
		vertexSubResourceData.pSysMem = vertices;

		ThrowIfBroke(direct3DDevice->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &m_VertexBuffer), "ID3D11Device::CreateBuffer() failed");
	}
}