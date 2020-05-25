#pragma once
#include <d3d11.h>

class SwapChain;

class GraphicsEngine
{
public:
	GraphicsEngine();
	// Init the graphics engine and DirectX 11 device
	bool init();
	// Release all the resources loaded
	bool release();
	~GraphicsEngine();

	static GraphicsEngine* get();
	
	SwapChain* createSwapChain();
private:
	ID3D11Device* d3d_device;
	D3D_FEATURE_LEVEL feature_level;
	ID3D11DeviceContext* imn_context;

	IDXGIDevice* dxgi_device;
	IDXGIAdapter* dxgi_adapter;
	IDXGIFactory* dxgi_factory;
private:
	friend class SwapChain;
};

