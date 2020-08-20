#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;

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
	DeviceContext* getImmediateDeviceContext();
private:
	ID3D11Device* d3d_device;
	D3D_FEATURE_LEVEL feature_level;


	IDXGIDevice* dxgi_device;
	IDXGIAdapter* dxgi_adapter;
	IDXGIFactory* dxgi_factory;

	DeviceContext* imn_device_context;
private:
	friend class SwapChain;
};

