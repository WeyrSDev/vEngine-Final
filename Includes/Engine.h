#pragma once
#include "stdafx.h"

using namespace vEngine;

namespace vEngine {
	class Engine {
	public:
		Engine(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
		virtual ~Engine();
		//
		HINSTANCE Instance() const;
		HWND WindowHandle() const;
		const WNDCLASSEX& Window() const;
		const std::wstring& WindowClass() const;
		const std::wstring& WindowTitle() const;
		int ScreenWidth() const;
		int ScreenHeight() const;
		//
		ID3D11Device1* Direct3DDevice() const;
		ID3D11DeviceContext1* Direct3DDeviceContext() const;
		bool DepthBufferEnabled() const;
		bool IsFullScreen() const;
		float AspectRatio() const;
		const D3D11_TEXTURE2D_DESC& BackBufferDesc() const;
		const D3D11_VIEWPORT& Viewport() const;
		const std::vector<EngineComponent*>& EngineComponents() const;
		const ServiceContainer& Services() const;
		//
		virtual void Run();
		virtual void Exit();
		virtual void Initialize();
		virtual void Update(const EngineTime& engineTime);
		virtual void Draw(const EngineTime& engineTime);
		//
	protected:
		//
		virtual void InitializeWindow();
		virtual void InitializeDirectX();
		virtual void Shutdown();

	protected:
		//
		static const UINT DefaultScreenWidth;
		static const UINT DefaultScreenHeight;
		static const UINT DefaultFrameRate;
		static const UINT DefaultMultiSamplingCount;
		//
	protected:
		//
		HINSTANCE m_Instance;
		std::wstring m_WindowClass;
		std::wstring m_WindowTitle;
		int m_ShowCommand;
		HWND m_WindowHandle;
		WNDCLASSEX m_Window;
		UINT m_ScreenWidth;
		UINT m_ScreenHeight;
		EngineClock m_EngineClock;
		EngineTime m_EngineTime;
		std::vector<EngineComponent*> m_EngineComponents;
		ServiceContainer m_Services;
		//
	protected:
		//
		D3D_FEATURE_LEVEL m_FeatureLevel;
		ID3D11Device1* m_Direct3DDevice;
		ID3D11DeviceContext1* m_Direct3DDeviceContext;
		IDXGISwapChain1* m_SwapChain;
		//
		UINT m_FrameRate;
		bool m_IsFullScreen;
		bool m_DepthStencilBufferEnabled;
		bool m_MultiSamplingEnabled;
		UINT m_MultiSamplingCount;
		UINT m_MultiSamplingQualityLevels;
		//
		ID3D11Texture2D* m_DepthStencilBuffer;
		D3D11_TEXTURE2D_DESC m_BackBufferDesc;
		ID3D11RenderTargetView* m_RenderTargetView;
		ID3D11DepthStencilView* m_DepthStencilView;
		D3D11_VIEWPORT m_Viewport;
		//
	private:
		//
		Engine(const Engine& rhs);
		Engine& operator=(const Engine& rhs);
		//
	private:
		//
		POINT CenterWindow(int windowWidth, int windowHeight);
		static LRESULT WINAPI WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
	};
}