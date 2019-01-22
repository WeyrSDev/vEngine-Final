#include "stdafx.h"

namespace vEngine {
	const UINT Engine::DefaultScreenWidth = 1024;
	const UINT Engine::DefaultScreenHeight = 768;
	const UINT Engine::DefaultFrameRate = 60;
	const UINT Engine::DefaultMultiSamplingCount = 4;

	Engine::Engine(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
		: m_Instance(instance), m_WindowClass(windowClass), m_WindowTitle(windowTitle), m_ShowCommand(showCommand),
		m_WindowHandle(), m_Window(),
		m_ScreenWidth(DefaultScreenWidth), m_ScreenHeight(DefaultScreenHeight),
		m_EngineClock(), m_EngineTime(),
		m_FeatureLevel(D3D_FEATURE_LEVEL_9_1), m_Direct3DDevice(nullptr), m_Direct3DDeviceContext(nullptr), m_SwapChain(nullptr),
		m_FrameRate(DefaultFrameRate), m_IsFullScreen(false),
		m_DepthStencilBufferEnabled(false), m_MultiSamplingEnabled(false), m_MultiSamplingCount(DefaultMultiSamplingCount), m_MultiSamplingQualityLevels(0),
		m_DepthStencilBuffer(nullptr), m_RenderTargetView(nullptr), m_DepthStencilView(nullptr), m_Viewport()
	{
	}

	Engine::~Engine()
	{
	}

	HINSTANCE Engine::Instance() const
	{
		return m_Instance;
	}

	HWND Engine::WindowHandle() const
	{
		return m_WindowHandle;
	}

	const WNDCLASSEX& Engine::Window() const
	{
		return m_Window;
	}

	const std::wstring& Engine::WindowClass() const
	{
		return m_WindowClass;
	}

	const std::wstring& Engine::WindowTitle() const
	{
		return m_WindowTitle;
	}

	int Engine::ScreenWidth() const
	{
		return m_ScreenWidth;
	}

	int Engine::ScreenHeight() const
	{
		return m_ScreenHeight;
	}

	ID3D11Device1* Engine::Direct3DDevice() const
	{
		return m_Direct3DDevice;
	}

	ID3D11DeviceContext1* Engine::Direct3DDeviceContext() const
	{
		return m_Direct3DDeviceContext;
	}

	float Engine::AspectRatio() const
	{
		return static_cast<float>(m_ScreenWidth) / m_ScreenHeight;
	}

	bool Engine::IsFullScreen() const
	{
		return m_IsFullScreen;
	}

	const D3D11_TEXTURE2D_DESC& Engine::BackBufferDesc() const
	{
		return m_BackBufferDesc;
	}

	const D3D11_VIEWPORT& Engine::Viewport() const
	{
		return m_Viewport;
	}

	void Engine::Run()
	{
		InitializeWindow();
		InitializeDirectX();
		Initialize();

		MSG message;
		ZeroMemory(&message, sizeof(message));

		m_EngineClock.Reset();

		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				m_EngineClock.UpdateEngineTime(m_EngineTime);
				Update(m_EngineTime);
				Draw(m_EngineTime);
			}
		}

		Shutdown();
	}

	void Engine::Exit()
	{
		PostQuitMessage(0);
	}

	void Engine::Initialize()
	{
	}

	void Engine::Shutdown()
	{
		ReleaseObject(m_RenderTargetView);
		ReleaseObject(m_DepthStencilView);
		ReleaseObject(m_SwapChain);
		ReleaseObject(m_DepthStencilBuffer);

		if (m_Direct3DDeviceContext != nullptr)
		{
			m_Direct3DDeviceContext->ClearState();
		}

		ReleaseObject(m_Direct3DDeviceContext);
		ReleaseObject(m_Direct3DDevice);

		UnregisterClass(m_WindowClass.c_str(), m_Window.hInstance);
	}

	void Engine::Update(const EngineTime& engineTime)
	{
	}

	void Engine::Draw(const EngineTime& engineTime)
	{
	}

	void Engine::InitializeWindow()
	{
		ZeroMemory(&m_Window, sizeof(m_Window));
		m_Window.cbSize = sizeof(WNDCLASSEX);
		m_Window.style = CS_CLASSDC;
		m_Window.lpfnWndProc = WndProc;
		m_Window.hInstance = m_Instance;
		m_Window.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		m_Window.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		m_Window.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_Window.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
		m_Window.lpszClassName = m_WindowClass.c_str();

		RECT windowRectangle = { 0, 0, m_ScreenWidth, m_ScreenHeight };
		AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

		RegisterClassEx(&m_Window);
		POINT center = CenterWindow(m_ScreenWidth, m_ScreenHeight);
		m_WindowHandle = CreateWindow(m_WindowClass.c_str(), m_WindowTitle.c_str(), WS_OVERLAPPEDWINDOW, center.x, center.y, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, nullptr, nullptr, m_Instance, nullptr);

		ShowWindow(m_WindowHandle, m_ShowCommand);
		UpdateWindow(m_WindowHandle);
	}

	void Engine::InitializeDirectX()
	{
		HRESULT hr;
		UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		ID3D11Device* direct3DDevice = nullptr;
		ID3D11DeviceContext* direct3DDeviceContext = nullptr;
		if (FAILED(hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &direct3DDevice, &m_FeatureLevel, &direct3DDeviceContext)))
		{
			throw EngineException("D3D11CreateDevice() failed", hr);
		}

		if (FAILED(hr = direct3DDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_Direct3DDevice))))
		{
			throw EngineException("ID3D11Device::QueryInterface() failed", hr);
		}

		if (FAILED(hr = direct3DDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_Direct3DDeviceContext))))
		{
			throw EngineException("ID3D11Device::QueryInterface() failed", hr);
		}

		ReleaseObject(direct3DDevice);
		ReleaseObject(direct3DDeviceContext);

		m_Direct3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_MultiSamplingCount, &m_MultiSamplingQualityLevels);
		if (m_MultiSamplingQualityLevels == 0)
		{
			throw EngineException("Unsupported multi-sampling quality");
		}

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.Width = m_ScreenWidth;
		swapChainDesc.Height = m_ScreenHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if (m_MultiSamplingEnabled)
		{
			swapChainDesc.SampleDesc.Count = m_MultiSamplingCount;
			swapChainDesc.SampleDesc.Quality = m_MultiSamplingQualityLevels - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		IDXGIDevice* dxgiDevice = nullptr;
		if (FAILED(hr = m_Direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
		{
			throw EngineException("ID3D11Device::QueryInterface() failed", hr);
		}

		IDXGIAdapter *dxgiAdapter = nullptr;
		if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter))))
		{
			ReleaseObject(dxgiDevice);
			throw EngineException("IDXGIDevice::GetParent() failed retrieving adapter.", hr);
		}

		IDXGIFactory2* dxgiFactory = nullptr;
		if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory))))
		{
			ReleaseObject(dxgiDevice);
			ReleaseObject(dxgiAdapter);
			throw EngineException("IDXGIAdapter::GetParent() failed retrieving factory.", hr);
		}

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
		ZeroMemory(&fullScreenDesc, sizeof(fullScreenDesc));
		fullScreenDesc.RefreshRate.Numerator = m_FrameRate;
		fullScreenDesc.RefreshRate.Denominator = 1;
		fullScreenDesc.Windowed = !m_IsFullScreen;

		if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, m_WindowHandle, &swapChainDesc, &fullScreenDesc, nullptr, &m_SwapChain)))
		{
			ReleaseObject(dxgiDevice);
			ReleaseObject(dxgiAdapter);
			ReleaseObject(dxgiFactory);
			throw EngineException("IDXGIDevice::CreateSwapChainForHwnd() failed.", hr);
		}

		ReleaseObject(dxgiDevice);
		ReleaseObject(dxgiAdapter);
		ReleaseObject(dxgiFactory);

		ID3D11Texture2D* backBuffer;
		if (FAILED(hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
		{
			throw EngineException("IDXGISwapChain::GetBuffer() failed.", hr);
		}

		backBuffer->GetDesc(&m_BackBufferDesc);

		if (FAILED(hr = m_Direct3DDevice->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView)))
		{
			ReleaseObject(backBuffer);
			throw EngineException("IDXGIDevice::CreateRenderTargetView() failed.", hr);
		}

		ReleaseObject(backBuffer);

		if (m_DepthStencilBufferEnabled)
		{
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
			depthStencilDesc.Width = m_ScreenWidth;
			depthStencilDesc.Height = m_ScreenHeight;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

			if (m_MultiSamplingEnabled)
			{
				depthStencilDesc.SampleDesc.Count = m_MultiSamplingCount;
				depthStencilDesc.SampleDesc.Quality = m_MultiSamplingQualityLevels - 1;
			}
			else
			{
				depthStencilDesc.SampleDesc.Count = 1;
				depthStencilDesc.SampleDesc.Quality = 0;
			}

			if (FAILED(hr = m_Direct3DDevice->CreateTexture2D(&depthStencilDesc, nullptr, &m_DepthStencilBuffer)))
			{
				throw EngineException("IDXGIDevice::CreateTexture2D() failed.", hr);
			}

			if (FAILED(hr = m_Direct3DDevice->CreateDepthStencilView(m_DepthStencilBuffer, nullptr, &m_DepthStencilView)))
			{
				throw EngineException("IDXGIDevice::CreateDepthStencilView() failed.", hr);
			}
		}

		m_Direct3DDeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

		m_Viewport.TopLeftX = 0.0f;
		m_Viewport.TopLeftY = 0.0f;
		m_Viewport.Width = static_cast<float>(m_ScreenWidth);
		m_Viewport.Height = static_cast<float>(m_ScreenHeight);
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;

		m_Direct3DDeviceContext->RSSetViewports(1, &m_Viewport);
	}


	LRESULT WINAPI Engine::WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(windowHandle, message, wParam, lParam);
	}

	POINT Engine::CenterWindow(int windowWidth, int windowHeight)
	{
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		POINT center;
		center.x = (screenWidth - windowWidth) / 2;
		center.y = (screenHeight - windowHeight) / 2;

		return center;
	}
}